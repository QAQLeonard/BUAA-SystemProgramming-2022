#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void source(int max)
{
    int i;
    for (i = 2; i <= max; i++)
    {
        write(1, &i, sizeof(i));
    }
}

void cull(int p)
{
    int n;
    while (read(0, &n, sizeof(n)))
    {
        if (n % p != 0)
        {
            write(1, &n, sizeof(n));
        }
    }
}

void redirect(int k, int pd[])
{
    close(k);
    dup(pd[k]);
    close(pd[0]);
    close(pd[1]);
}

void sink()
{
    int pd[2];
    int p;
    if (read(0, &p, sizeof(p)))
    {
        printf("%d\n", p);
        pipe(pd);
        if (fork())
        {
            redirect(0, pd);
            sink();
        }
        else
        {
            redirect(1, pd);
            cull(p);
        }
    }
}

int main(int argc, char* argv[])
{
    int pd[2];
    pipe(pd);
    if (fork() > 0)
    { // 父进程
        // 重定向标准输入文件到pd[0]
        redirect(0, pd);
        sink();
    }
    else
    {
        //子进程重定向标准输出文件到pd[1]
        redirect(1, pd);
        source(atoi(argv[1]));
    }
    exit(0);
}