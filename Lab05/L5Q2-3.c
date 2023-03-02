#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define PATHNAME_MAX 1000

int main()
{
    pid_t pid = fork();
    pid_t pid0 = fork();
    if (pid > 0 && pid0 > 0)
    {
        sleep(2);
        if (execl("/bin/rm", "rm", "-f", "L5Q1-1", (char *) 0) == -1)
        {
            fprintf(stderr, "execl error: %s", strerror(errno));
            exit(1);
        }
    }
    else if (pid == 0 && pid0 > 0)
    {
        if (execl("./L5Q1-1", "L5Q1-1", "0", "1", "1",(char *) 0) == -1)
        {
            fprintf(stderr, "execl error: %s", strerror(errno));
            exit(1);
        }
    }
    else if (pid0 == 0 && pid > 0)
    {
        sleep(1);
        if (execl("./L5Q1-1", "L5Q1-1", "1", "1", "1",(char *) 0) == -1)
        {
            fprintf(stderr, "execl error: %s", strerror(errno));
            exit(1);
        }
    }
    return 0;
}
