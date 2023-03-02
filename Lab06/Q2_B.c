#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
void sigHandler(int sig, siginfo_t *info, void *ucontext)
{
    printf("Signal value is %d\n", info->si_value.sival_int);
}

int main()
{
    int pid = getpid();
    printf("My PID is %d\n", pid);
    struct sigaction act;
    act.sa_sigaction = sigHandler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &act, NULL);
    while (1)
    {
        sleep(1);
    }
    return 0;
}