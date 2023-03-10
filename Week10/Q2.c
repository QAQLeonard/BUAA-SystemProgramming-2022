#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define MSG "Catch signal SIGINT processing \n"
#define MSG_END "Finished process SIGINT return \n"

void time_fun()
{
    long long s = 0;
    long long i;
    for (i = 0; i < 500000000L; i++)
    {
        s += i;
    }
}

static void sig_handler(int signuum)
{
    /*
    在信号处理程序中，尽量不要调用与标准IO相关的和不可重入的函数。
    STDIN_FILENO：接收键盘的输入
    STDOUT_FILENO：向屏幕输出
     */
    write(STDOUT_FILENO, MSG, strlen(MSG));
    time_fun();
    write(STDOUT_FILENO, MSG_END, strlen(MSG_END));
}


int main(int argc, char **argv)
{

    // 注册信号处理函数
    if (SIG_ERR == signal(SIGINT, sig_handler))
    {
        fprintf(stderr, "signal error "), perror("");
        exit(1);
    }

    // 让主程序不退出，挂起，等待信号产生
    while (1)
    {
        pause(); //使调用进程在接到一信号前挂起。
    }
    return 0;
}