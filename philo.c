/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:34:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/23 14:57:28 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>


void* thread_logic(void *pnt)
{
    int *num =(int *) pnt;
    printf("hello thread = %d\n", 5);

    return (NULL);
}



int main ()
{
    pthread_t t1;
    pthread_t t2;
    int num;


    num = 5;
    pthread_create(&t1, NULL, &thread_logic, (void *)&num);
    pthread_create(&t2, NULL, &thread_logic,(void *)&num);
    while (1);
    return (0);
}