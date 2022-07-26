/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:34:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/26 15:53:57 by ahmez-za         ###   ########.fr       */
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
    while ((get_curr_time() - now) < duration)
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

int    check_if_philo_eat_at_least(t_philo *philos, t_data *data)
{
    int i;
    int k;

    i = 0;
    k = 0;
    while (i < data->number_of_philos )
    {
    pthread_mutex_lock(&data->meals_count_mutex);

        if (philos[i].meals_count >= data->number_of_meals)
            k++;
        i++;
    pthread_mutex_unlock(&data->meals_count_mutex);

    }
    if (k == i)
        return (1);
    return (0);
    
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
    ft_print_philos(philo, 0);
    pthread_mutex_lock(&philo->data->forks[(philo->id) % philo->data->number_of_philos]);
    ft_print_philos(philo, 0);
    ft_print_philos(philo, -1);
    ft_usleep(philo->data->time_to_eat);
    pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
    pthread_mutex_unlock(&philo->data->forks[(philo->id) % philo->data->number_of_philos]);

    pthread_mutex_lock(&philo->data->meals_count_mutex);
    if(philo->data->number_of_meals != -1)
        philo->meals_count += 1;
    pthread_mutex_unlock(&philo->data->meals_count_mutex);
    
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



void parsing_arguments(int ac , char **argv, t_data *data)
{
    pthread_mutex_init(&data->meals_count_mutex, NULL);
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
    t_data *data;
    t_philo *philos;
    i = 0;

    data = malloc(sizeof(t_data));
    parsing_arguments(ac, argv, data);
    philos = malloc (sizeof(t_philo) * data->number_of_philos);
    philosophers = malloc(sizeof(pthread_t) * data->number_of_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);

    pthread_mutex_init(&data->philo_print, NULL);
    while (i < data->number_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_count = 0;
        philos[i].data = data;

        pthread_mutex_init(&data->forks[i++], NULL);

    }
    i = 0;
    while (i < data->number_of_philos)
    {
            pthread_create(&philosophers[i], NULL, &thread_logic, (void *) &philos[i]);
            i++;
            // usleep(100);
    }
    while (1)
    {
        if(check_if_philo_eat_at_least(philos, data))
            break;
    }
    return (0);
}