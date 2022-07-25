/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 03:55:42 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/24 19:16:07 by sben-chi         ###   ########.fr       */
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
		ft_error();
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - '0');
		// if (number > 2147483647)
		// 	return (0);
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Error: wrong argements\n");
		exit(1);
	}
	return (number * sign);
}



// void	ft_usleep(long long time)
// {
// 	long long	num;

// 	num = get_current_time();
// 	while (get_current_time() - num < time)
// 		usleep(500);
// }

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (1);
// 	else
//         return (0);
// }


void	ft_error()
{
	printf("Error: Invalid Arguments\n");
	exit(1);
}