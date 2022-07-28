/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 03:55:42 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/28 02:30:32 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (((str[i] >= 7 && str[i] <= 13) || (str[i] == ' ')))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - '0');
		if (number > 9223372036854775807)
			return (0);
		i++;
	}
	if (str[i] != '\0' || str[0] == '\0')
	{
		return (-1);
	}
	return (number * sign);
}

time_t	get_curr_time(void)
{
	time_t			time;
	struct timeval	start;

	gettimeofday(&start, NULL);
	time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (time);
}

void	ft_usleep(time_t duration)
{
	time_t	now;

	now = get_curr_time();
	while ((get_curr_time() - now) < duration)
	{
		usleep(50);
	}
}

void	ft_print_philos(t_philo *philo, char *message)
{
	time_t	time;

	time = get_curr_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->philo_print);
	if (philo->data->is_died == 1)
		printf(" ");
	else
	{
		printf("[%ld] %d %s\n", time, philo->id, message);
		if (message[0] == 'd')
			philo->data->is_died = 1;
	}
	pthread_mutex_unlock(&philo->data->philo_print);
}
