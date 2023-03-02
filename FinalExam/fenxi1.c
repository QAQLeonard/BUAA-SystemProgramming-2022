#include <stdio.h>
#include <unistd.h>
int main()
{
    int pid, i;
    pid = 0;
    for (i = 1; i <= 3; i++)
    {
        pid = fork();
        printf("%d\n", i);
    }
    if (pid > 0)
        printf("ok\n");
}
