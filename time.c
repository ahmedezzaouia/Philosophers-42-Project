
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

int my_get_time()
{
    struct timeval start;
    static int time;
    int startt;
    struct timeval end;
    int endd;
    gettimeofday(&start, NULL);
    startt = (start.tv_sec * 1000) + (start.tv_usec / 1000);
//  printf("i %d\n", startt);
    usleep(500 * 1000);
    gettimeofday(&end, NULL);
    endd = (end.tv_sec * 1000) + (end.tv_usec / 1000);
//  printf("f %d\n", endd);
    time += endd - startt;
    //return (time);
    printf("time :  %d\n", time);
}

int main()
{
    for(int i = 0; i < 10; i++)
    my_get_time();
}