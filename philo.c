/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:34:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/28 02:11:42 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_count = 0;
		philos[i].data = data;
		philos[i].last_meal_time = philos[i].data->start_time;
		pthread_mutex_init(&data->forks[i++], NULL);
	}
}

void	create_threads(pthread_t *philosophers, t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_create(&philosophers[i], NULL, &routine, (void *) &philos[i]);
		i++;
		usleep(100);
	}
}

int	main(int ac, char **argv)
{
	int			i;
	pthread_t	*philosophers;
	t_data		*data;
	t_philo		*philos;

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
	init_philos(philos, data);
	i = 0;
	create_threads(philosophers, philos, data);
	while (1)
	{
		if (check_if_at_least_or_die(philos, data))
			break ;
	}
	return (0);
}
