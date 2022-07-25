/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:34:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/25 20:23:38 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int get_curr_time()
{
    unsigned int time;
    struct timeval start;

    gettimeofday(&start, NULL);
    time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
    return (time);

}

void ft_usleep(unsigned int duration)
{
   unsigned int now; 

    now = get_curr_time();
    while (get_curr_time() - now < duration)
    {
        usleep(50);
    }
    
}

void    ft_print_philos (t_philo *philo, int cycle)
{
    unsigned int time;

    time = get_curr_time() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->philo_print);
    if (!cycle)
    {
       printf("[%d] %d has taken a fork\n",time, philo->id);
    }
    else if (cycle == -1)
    {

        printf("[%d] %d philo Eating\n", time, philo->id);
    }
    
    else if (cycle == 1)
    {
        
         printf("[%d] %d philo sleeping\n", time, philo->id); 
    }
    else if (cycle == 2)
    {
        printf("[%d] %d philo thinking\n",time, philo->id);
    }
    pthread_mutex_unlock(&philo->data->philo_print);
        
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->id]);
    ft_print_philos(philo, 0);
    pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->number_of_philos]);
    ft_print_philos(philo, 0);
    ft_print_philos(philo, -1);
    ft_usleep(philo->data->time_to_eat);
    pthread_mutex_unlock(&philo->data->forks[philo->id]);
    pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->number_of_philos]);
}

void    sleeping(t_philo *philo)
{
    

    ft_print_philos(philo, 1);
    ft_usleep(philo->data->time_to_sleep);

}

void    thinking(t_philo *philo)
{
    ft_print_philos(philo, 2);
}


void* thread_logic(void *ph)
{
   t_philo *philo = (t_philo *) ph;
    
    while(1)
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return (NULL);
}



void parsing_arguments(int ac , char **argv, t_data *data)
{
    if (ac != 5 && ac != 6)
        ft_error();

        if (ft_atoi(argv[1]) == 0)
            ft_error();
        data->start_time = get_curr_time();
        data->number_of_philos =  ft_atoi(argv[1]);
        data->time_to_die =  ft_atoi(argv[2]);
        data->time_to_eat =  ft_atoi(argv[3]);
        data->time_to_sleep =  ft_atoi(argv[4]);
        if (ac == 6)
            data->number_of_meals =  ft_atoi(argv[5]);
        else
            data->number_of_meals =  -1;
 
}


int main (int ac , char **argv)
{
    int i;
    pthread_t *philosophers;
    // t_philo philo;
    t_data data;
    t_philo *philos;
    i = 0;
    parsing_arguments(ac, argv, &data);
    // printf("number_of_philos = %d\n", philo.data.number_of_philos);
    // printf("time_to_die = %d\n", philo.data.time_to_die);
    
    // printf("***********************************\n");

    philos = malloc (sizeof(t_philo) * data.number_of_philos);
    philosophers = malloc(sizeof(pthread_t) * data.number_of_philos);
    data.forks = malloc(sizeof(int) * data.number_of_philos);
    pthread_mutex_init(&data.philo_print, NULL);
    while (i < data.number_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_count = 0;
        philos[i].data = &data;
        pthread_mutex_init(&data.forks[i++], NULL);

    }
    i = 0;
    while (i < data.number_of_philos)
        {
            // philo.id = i + 1;
            pthread_create(&philosophers[i], NULL, &thread_logic, (void *) &philos[i]);
            i++;
            ft_usleep(100);
        }
    while(1);
    return (0);
}