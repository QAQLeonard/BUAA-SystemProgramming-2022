#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int pid = atoi(argv[1]);
    int ID = atoi(argv[2]);
    sigqueue(pid, SIGINT, (union sigval)ID);
    return 0;
}