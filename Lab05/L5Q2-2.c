#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define PATHNAME_MAX 1000

int main()
{
    char buf[PATHNAME_MAX];

    /* 使用getcwd获取启动目录 */
    if (getcwd(buf, sizeof(buf))==NULL)
    {
        fprintf(stderr, "getcwd error: %s", strerror(errno));
        exit(1);
    }
    //printf("current work path: %s\n", buf);
    if(execl("/bin/ls", "ls", "-l",buf, (char *) 0)==-1)
    {
        fprintf(stderr, "execl error: %s", strerror(errno));
        exit(1);
    }
    return 0;
}
