/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:29:20 by sben-chi          #+#    #+#             */
/*   Updated: 2022/07/24 22:21:54 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct s_data {
    unsigned int number_of_philos;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    unsigned int number_of_meals;
    pthread_mutix *forks;
} t_data;


typedef struct s_philo {
    int id;
    int meals_count;
    t_data *data;

    
} t_philo;


long long ft_atoi(const char *str);
int	ft_strlen(char *str);
void	ft_error();

#endif