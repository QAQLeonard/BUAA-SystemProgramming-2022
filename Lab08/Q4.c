#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int current = 0; //生产者运行加一，消费者运行减一
int buf[20];     //缓冲区
int in = 0, out = 0;
int items = 0, spaces = 20;
int flag;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
    while (flag != 0)
    {
        pthread_mutex_lock(&mutex);
        while (!spaces)
        {
            pthread_cond_wait(&notfull, &mutex);
        }
        buf[in] = current++;
        in = (in + 1) % 20;
        items++;
        spaces--;
        printf("producer %zu , current = %d\n", pthread_self(), current);
        for (int i = 0; i < 20; i++)
        {
            if (buf[i] != -1)
            {
                printf("%-4d", buf[i]);
            }
        }
        printf("\n\n");

        pthread_cond_signal(&notempty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    while (flag != 0)
    {
        pthread_mutex_lock(&mutex);
        while (!items)
        {
            pthread_cond_wait(&notempty, &mutex);
        }
        buf[out] = -1;
        out = (out + 1) % 20;
        current--;
        items--;
        spaces++;
        printf("consumer %zu ,current = %d\n", pthread_self(), current);
        for (int i = 0; i < 20; i++)
        {
            if (buf[i] != -1)
            {
                printf("%-4d", buf[i]);
            }
        }
        printf("\n\n");

        pthread_cond_signal(&notfull);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    memset(buf, -1, sizeof(buf));
    flag = 1;
    pthread_t pro[10], con[10];
    int i = 0;
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&pro[i], NULL, producer, NULL);
        pthread_create(&con[i], NULL, consumer, NULL);
    }
    sleep(1);
    flag = 0;
    for (int i = 0; i < 10; i++)
    {
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }
    return 0;
}