/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:29:20 by sben-chi          #+#    #+#             */
/*   Updated: 2022/07/26 19:42:14 by ahmez-za         ###   ########.fr       */
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

#endif