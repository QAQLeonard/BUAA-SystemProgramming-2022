#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    close(1);
    char buf[] = "21373339";
    int fd = open("./student.txt", O_WRONLY | O_CREAT, 0644);
    printf("%s\n", buf);
}