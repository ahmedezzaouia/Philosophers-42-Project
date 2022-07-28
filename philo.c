/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:34:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/28 00:53:37 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t get_curr_time()
{
    time_t time;
    struct timeval start;

    gettimeofday(&start, NULL);
    time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
    return (time);

}

void ft_usleep(time_t duration)
{
   time_t now; 

    now = get_curr_time();
    while ((get_curr_time() - now) < duration)
    {
        usleep(50);
    }
    
}

void    ft_print_philos (t_philo *philo, int cycle)
{
    time_t time;

    time = get_curr_time() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->philo_print);
    if (philo->data->is_died == 1)
    {
        printf(" ");
    }
    else if (!cycle)
    {
       printf("[%ld] %d has taken a fork\n",time, philo->id);
    }
    else if (cycle == -1)
    {

        printf("[%ld] %d philo Eating\n", time, philo->id);
    }
    
    else if (cycle == 1)
    {
        
         printf("[%ld] %d philo sleeping\n", time, philo->id); 
    }
    else if (cycle == 2)
    {
        printf("[%ld] %d philo thinking\n",time, philo->id);
    }
    else if (cycle == 3)
    {
        printf("[%ld] %d died\n",time, philo->id);
        philo->data->is_died = 1;
    }
    pthread_mutex_unlock(&philo->data->philo_print);
        
}

int    check_if_philo_eat_at_least(t_philo *philos, t_data *data)
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
                        ft_print_philos(&(philos[i]), 3);
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

int    check_if_philo_is_die(t_philo *philos, t_data *data)
{
    int i;

    i = 0;

    
    while (i < data->number_of_philos)
    {
    pthread_mutex_lock(&data->last_meals_time_mutex);
        if ((get_curr_time() - philos[i].last_meal_time) > data->time_to_die)
        {
        printf("philo %d last meal time == %ld --- time to die == %ld\n",philos[i].id, get_curr_time() - philos[i].last_meal_time, data->time_to_die);
                ft_print_philos(&(philos[i]), 3);
                return(1);
        }
        i++;
    pthread_mutex_unlock(&data->last_meals_time_mutex);
    }
    
    return (0);
    
}

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



int main (int ac , char **argv)
{
    int i;
    pthread_t *philosophers;
    t_data *data;
    t_philo *philos;
    i = 0;

    data = malloc(sizeof(t_data));
    if (!parsing_arguments(ac, argv, data))
    {
        printf("error: invalid Arguments\n");
        return (0);
    }
    philos = malloc (sizeof(t_philo) * data->number_of_philos);
    philosophers = malloc(sizeof(pthread_t) * data->number_of_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);

    pthread_mutex_init(&data->philo_print, NULL);
    while (i < data->number_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_count = 0;
        philos[i].data = data;
        philos[i].last_meal_time = philos[i].data->start_time;
        pthread_mutex_init(&data->forks[i++], NULL);

    }
    i = 0;
    while (i < data->number_of_philos)
    {
            pthread_create(&philosophers[i], NULL, &thread_logic, (void *) &philos[i]);
            i++;
            usleep(100);
    }
    while (1)
    {
        if(check_if_philo_eat_at_least(philos, data))
            break;
    }
    return (0);
}