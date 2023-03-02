#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
int count = 0;
pthread_mutex_t mutex;
pthread_cond_t cond1, cond2;

void *thread1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (count >= 100)
        {
            exit(1);
        }
        printf("thread1: %d \n", count);
        count++;
        pthread_cond_signal(&cond2);
        pthread_cond_wait(&cond1, &mutex);
        pthread_mutex_unlock(&mutex);
        // sleep(1);
    }
}
void *thread2(void *arg)
{
    usleep(100); //保证是线程1先打印
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("thread2: %d \n", count);
        count++;
        pthread_cond_signal(&cond1);
        pthread_cond_wait(&cond2, &mutex);
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_t pid1, pid2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond1, NULL);
    pthread_cond_init(&cond2, NULL);

    pthread_create(&pid1, NULL, thread1, NULL);
    pthread_create(&pid2, NULL, thread2, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    return 0;
}