#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

int status;

void catch (int sigNum)
{
    pid_t wpid;

    while ((wpid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("father wait son pid is %d\n Exit code is %d\n", wpid, status);
    }
}

int main()
{

    sigset_t myset, oldset;
    sigemptyset(&myset);
    sigaddset(&myset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &myset, &oldset);
    pid_t pid;
    int i;
    for (i = 0; i < 5; ++i)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
    }
    if (i == 5)
    {

        sleep(2);
        struct sigaction act;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        act.sa_handler = catch;
        sigaction(SIGCHLD, &act, NULL);

        sigprocmask(SIG_SETMASK, &oldset, NULL);
        while (1)
        {
            sleep(1);
        }
    }
    else if (i < 5)
    {
        printf("son process pid is %d\n", getpid());
        exit(i);
    }
    return 0;
}
