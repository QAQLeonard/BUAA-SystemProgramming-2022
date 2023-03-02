#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_cond_t cond1, cond2;
pthread_mutex_t mu;

void *eat1(void *args)
{

    printf("1 eat\n");
    pthread_cond_signal(&cond2);
    while (1)
    {
        puts("code1 before pthread_con_wait");
        pthread_cond_wait(&cond1, &mu);
        puts("1 eat\n");
        pthread_cond_signal(&cond2);
    }
}

void *eat2(void *args)
{
    while (1)
    {
        puts("code2 before pthread_con_wait");
        pthread_cond_wait(&cond2, &mu);
        puts("2 eat\n");
        pthread_cond_signal(&cond1);
    }
}

int main(void)
{

    pthread_mutex_init(&mu, NULL);

    pthread_cond_init(&cond1, NULL);

    pthread_cond_init(&cond2, NULL);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, eat1, NULL);

    pthread_create(&t2, NULL, eat2, NULL);

    pthread_join(t1, NULL);

    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mu);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
}
