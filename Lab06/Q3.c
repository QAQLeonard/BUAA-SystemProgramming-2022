#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

char s;

void stop(int sigNum)
{
    exit(0);
}

void input()
{
    scanf("%c", &s);
    if (s == 'N')
    {
        alarm(0);
    }
    else
    {
        exit(0);
    }
}

void ask(int sigNum)
{
    printf("If stop the program? (Y/N)\n");
    signal(SIGALRM, stop);
    alarm(5);
    input();
}

int main()
{
    signal(SIGINT, ask);
    while (1)
    {
        printf("21373339\n");
        sleep(1);
    }
}