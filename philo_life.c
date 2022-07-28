/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:50:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/28 01:52:20 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
    ft_print_philos(philo, 0);
    pthread_mutex_lock(&philo->data->forks[(philo->id) % philo->data->number_of_philos]);
    
    pthread_mutex_lock(&philo->data->last_meals_time_mutex);
    philo->last_meal_time = get_curr_time();
    pthread_mutex_unlock(&philo->data->last_meals_time_mutex);

    ft_print_philos(philo, 0);
    ft_print_philos(philo, -1);

    ft_usleep(philo->data->time_to_eat);
    // pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
    // pthread_mutex_unlock(&philo->data->forks[(philo->id) % philo->data->number_of_philos]);

    pthread_mutex_lock(&philo->data->meals_count_mutex);
    if(philo->data->number_of_meals != -1)
        philo->meals_count += 1;
    pthread_mutex_unlock(&philo->data->meals_count_mutex);

            printf("number of meals == %d && meal count == %d\n",philo->data->number_of_meals,  philo->meals_count );


    
}

void    sleeping(t_philo *philo)
{
    

    ft_print_philos(philo, 1);
    pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
    pthread_mutex_unlock(&philo->data->forks[(philo->id) % philo->data->number_of_philos]);
    ft_usleep(philo->data->time_to_sleep);

}

void    thinking(t_philo *philo)
{
    ft_print_philos(philo, 2);
}


void* routine(void *ph)
{
   t_philo *philo = (t_philo *) ph;
    
   
    if (!(philo->id % 2))
        usleep(100);
    while(1)
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return (NULL);
}

