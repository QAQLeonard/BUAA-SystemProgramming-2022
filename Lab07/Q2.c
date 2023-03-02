#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
sem_t *sem1, *sem2, *sem3;
int a[8] = {2, 1, 3, 7, 3, 3, 3, 9};
pid_t pid, pid0, pid1;

int main(int argc, char **argv)
{
    sem_t *sem1, *sem2, *sem3;
    sem1 = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(sem1, 1, 1);
    sem2 = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(sem2, 1, 0);
    sem3 = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(sem3, 1, 0);
    char *ch;
    ch = (char *)mmap(NULL, sizeof(char) * 2005, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *temp;
    temp = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    pid = fork();

    if (pid == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            if (sem_wait(sem1) == 0)
            {
                ch[*temp] = 'A';
                (*temp)++;
                ch[*temp] = a[i] + '0';
                (*temp)++;
                sem_post(sem2);
            }
        }
    }
    else
    {
        pid1 = fork();
        if (pid1 == 0)
        {

            for (int i = 0; i < 8; i++)
            {
                if (sem_wait(sem2) == 0)
                {
                    ch[*temp] = 'B';
                    (*temp)++;
                    ch[*temp] = a[i] + '0';
                    (*temp)++;
                    sem_post(sem3);
                }
            }
        }
        else
        {

            for (int i = 0; i < 8; i++)
            {
                if (sem_wait(sem3) == 0)
                {
                    ch[*temp] = 'C';
                    (*temp)++;
                    ch[*temp] = a[i] + '0';
                    (*temp)++;
                    sem_post(sem1);
                }
            }
            ch[*temp] = '\0';
            printf("%s", ch);
        }
    }

    sem_destroy(sem1);
    sem_destroy(sem2);
    sem_destroy(sem3);
}
