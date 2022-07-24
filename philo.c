/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:34:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/07/24 04:52:18 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>



void    eating()
{
     
    printf("philo take the left fork\n") ;
    //lock
    printf("philo take the right fork\n") ;

    printf("philo Eating\n");
    sleep(3);
    //unlock
    //unlock
}

void    sleeping()
{
    printf("philo sleeping\n");
    sleep(3);

}

void    thinking()
{
    printf("philo thinking\n");
}


void* thread_logic()
{
    while(1)
    {
        eating();
        sleeping();
        thinking();
    }
    sleep(3);
    return (NULL);
}



void parsing_arguments(int ac , char **argv)
{
    int i;

    i = 1;
    while (i < ac - 1)
    {
         
    }
    
}


int main (int ac , char **argv)
{
    int i;
    pthread_t *threads;
    i = 0;
    while (i < 5)
    {
        pthread_create(&threads[i], NULL, &thread_logic, NULL);
        i++;
        sleep(3);
    }
    while(1);
    return (0);
}