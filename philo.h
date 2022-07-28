/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:29:20 by sben-chi          #+#    #+#             */
/*   Updated: 2022/07/28 01:56:27 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
 #include <sys/time.h>


typedef struct s_data {
    int number_of_philos;
    time_t time_to_die;
    time_t time_to_eat;
    time_t time_to_sleep;
    int number_of_meals;
    pthread_mutex_t *forks;
    pthread_mutex_t philo_print;
    time_t start_time;
    pthread_mutex_t meals_count_mutex;
    pthread_mutex_t last_meals_time_mutex;
    int is_died;

} t_data;


typedef struct s_philo {
    int id;
    int meals_count;
    time_t last_meal_time;
    t_data *data;
    
} t_philo;


long long ft_atoi(const char *str);
int	ft_strlen(char *str);
void	ft_error();
time_t get_curr_time();
void ft_usleep(time_t duration);
void    ft_print_philos (t_philo *philo, int cycle);
void    eating(t_philo *philo);
void    sleeping(t_philo *philo);
void    thinking(t_philo *philo);
void* routine(void *ph);
int    check_if_at_least_or_die(t_philo *philos, t_data *data);
int parsing_arguments(int ac , char **argv, t_data *data);


#endif