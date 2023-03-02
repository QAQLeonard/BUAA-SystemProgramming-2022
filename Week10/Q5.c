#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int n = 0;
static void sigHandler(int signuum)
{
    time_t t = time(NULL);
    n++;
    printf("%d %s", n, ctime(&t));
}

int main()
{
    signal(SIGINT, sigHandler);
    pid_t pid = getpid();
    while (1) 
    {
        kill(pid, SIGINT);
        sleep(1);
    }    
    return 0;
}
