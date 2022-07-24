/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:34:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/24 22:23:59 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    eating()
{
    
    printf("philo take the left fork\n");
    //lock
    printf("philo take the right fork\n");

    printf("philo Eating\n");
    sleep(3);
    //unlock
}

void    sleeping()
{
    printf("philo sleeping\n");
    sleep(3);

}

void    thinking()
{
    printf("philo thinking\n");
}


void* thread_logic()
{
    while(1)
    {
        eating();
        
        sleeping();
        thinking();
    }
    sleep(3);
    return (NULL);
}



void parsing_arguments(int ac , char **argv, t_data *data)
{
    if (ac != 5 && ac != 6)
        ft_error();

        if (ft_atoi(argv[1]) == 0)
            ft_error();

        data->number_of_philos =  ft_atoi(argv[1]);
        data->time_to_die =  ft_atoi(argv[2]);
        data->time_to_eat =  ft_atoi(argv[3]);
        data->time_to_sleep =  ft_atoi(argv[4]);
        if (ac == 6)
            data->time_to_eat =  ft_atoi(argv[5]);
        else
            data->time_to_eat =  -1;
 
    
    
}


int main (int ac , char **argv)
{
    int i;
    pthread_t *threads;
    t_data data;
    
    i = 0;
    parsing_arguments(ac, argv, &data);
    printf("number_of_philos = %d\n", data.number_of_philos);
    printf("time_to_die = %d\n", data.time_to_die);
    
    printf("***********************************\n");

    threads = malloc(sizeof(pthread_t) * data.number_of_philos);
    data.forks = malloc(sizeof(int) * data.number_of_philos);
   while (i < data.number_of_philos)
    {
        pthread_create(&threads[i], NULL, &thread_logic, NULL);
        data.forks[i] = i + 1;
        i++;
        sleep(3);
    }
    while(1);
    return (0);
}