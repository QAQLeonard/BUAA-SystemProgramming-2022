#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


pid_t pid_p, pid_c;
void ID(int sigNum)
{
    printf("21373339\n");
    sleep(1);
    kill(pid_c, SIGALRM);
}

void Name(int sigNum)
{
    printf("Leonard Zhou\n");
    sleep(1);
    kill(pid_p, SIGINT);
}

int main(int argc, char **argv)
{
    signal(SIGINT, ID);
    signal(SIGALRM, Name);
    int status;
    pid_p = getpid();
    pid_c = fork();
    if (pid_c == 0)//child
    {
        sleep(1);
        kill(pid_p, SIGINT);
    }
    else
    {   
        sleep(2);
        kill(pid_c, SIGALRM);
    }
    while (1)
        ;
}