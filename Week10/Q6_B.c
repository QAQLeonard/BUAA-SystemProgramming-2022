#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
char *st[10];
int s;
void sigHandler(int signalNum)
{
    printf("B: ");
    for (int i = 1; i < s; i++)
        printf("%s ", st[i]);
    printf("\n");
}
int main(int argc, char *argv[])
{
    printf("The pid of B is %d\n", getpid());
    s = argc;
    for (int i = 1; i <= argc; i++)
        for (int i = 1; i <= argc; i++)
            st[i] = argv[i];
    signal(SIGINT, sigHandler);
    while (1)
        ;
}