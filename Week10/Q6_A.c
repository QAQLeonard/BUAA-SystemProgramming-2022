#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int pid = atoi(argv[1]);
    int time = atoi(argv[2]);
    printf("A: send a signal to B after %d seconds\n...\n", time);
    sleep(time);
    printf("A: send a signal to B\n");
    kill(pid, SIGINT);
    return 0;
}