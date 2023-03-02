#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <time.h>
sem_t *sem1, *sem2, *sem3;
pid_t pid;

int main(int argc, char **argv)
{
    sem_t *sem1, *sem2;
    sem1 = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(sem1, 1, 1);
    sem2 = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(sem2, 1, 0);
    int *data;
    data = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

    pid = fork();
    srand((int)time(NULL));
    if (pid == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (sem_wait(sem1) == 0)
            {
                *data = rand();
                printf("write: %d\n", *data);
                sem_post(sem2);
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            if (sem_wait(sem2) == 0)
            {
                printf("read:  %d\n", *data);
                sem_post(sem1);
            }
        }
    }
    sem_destroy(sem1);
    sem_destroy(sem2);
    munmap(data,sizeof(int));
    return 0;
}
