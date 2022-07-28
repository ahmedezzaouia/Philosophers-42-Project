/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:53:53 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/28 02:21:30 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    check_if_at_least_or_die(t_philo *philos, t_data *data)
{
    int i;
    int k;

    i = 0;
    k = 0;

    pthread_mutex_lock(&data->meals_count_mutex);

    while (i < data->number_of_philos )
        {
            // printf("number of meals == %d && meal count == %d\n",data->number_of_meals,  philos[i].meals_count );
            pthread_mutex_lock(&data->last_meals_time_mutex);
            if ((get_curr_time() - philos[i].last_meal_time) >= data->time_to_die)
                {
                    printf("philo %d last meal time == %ld --- time to die == %ld\n",philos[i].id, get_curr_time() - philos[i].last_meal_time, data->time_to_die);
                        ft_print_philos(&(philos[i]), "died");
                        return(1);
                }
            pthread_mutex_unlock(&data->last_meals_time_mutex);
            if (philos[i].meals_count >= data->number_of_meals)
                k++;
            i++;
        }
    pthread_mutex_unlock(&data->meals_count_mutex);
    if (k == data->number_of_philos && data->number_of_meals != -1)
        return (1);
    return (0);
    
}

int parsing_arguments(int ac , char **argv, t_data *data)
{
    pthread_mutex_init(&data->meals_count_mutex, NULL);
    pthread_mutex_init(&data->last_meals_time_mutex, NULL);
    if (ac != 5 && ac != 6)
        return (0);

    if (ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1 || ft_atoi(argv[3]) == -1 || ft_atoi(argv[4]) == -1)
        return (0);
        if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0)
            return (0);
        data->is_died = 0;
        data->start_time = get_curr_time();
        data->number_of_philos =  ft_atoi(argv[1]);
        data->time_to_die =  ft_atoi(argv[2]);
        data->time_to_eat =  ft_atoi(argv[3]);
        data->time_to_sleep =  ft_atoi(argv[4]);
        
        if (ac == 6)
        {
            data->number_of_meals =  ft_atoi(argv[5]);
            if (data->number_of_meals == 0 ||data->number_of_meals == -1)
                return (0);
        }
        else
            data->number_of_meals =  -1;

        return (1);
 
}