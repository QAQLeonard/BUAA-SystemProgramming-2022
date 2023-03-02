#include <stdio.h>
#include <pthread.h>

#define thread_num 5

int counter;

void *add(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        counter++;
    }
}

int main()
{
    pthread_t tids[thread_num];
    for (int i = 0; i < thread_num; i++)
    {
        pthread_create(&tids[i], NULL, add, NULL);
        pthread_join(tids[i], NULL);
    }
    printf("counter=%d\n", counter);
}