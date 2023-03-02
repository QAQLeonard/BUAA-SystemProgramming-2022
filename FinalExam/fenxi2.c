#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])

{
    if ((argc == 3) && (strcmp(argv[1], argv[2]) != 0))
    { // 保证有 3 个参数，而且源文件和目的文件名字不能一样

        int fd_src, fd_dest, ret;
        // 只读方式打开源文件
        fd_src = open(argv[1], O_RDONLY);
        if (fd_src < 0)
        {
            perror("open argv[1]");
            return -1;
        }
        // 新建目的文件
        fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

        if (fd_dest < 0)
        {
            close(fd_src);
            perror("open argv[2]");
            return -1;
        }
        do
        {
            char buf[1024] = {0};
            // 从源文件读取数据
            ret = read(fd_src, buf, sizeof(buf));
            // 把数据写到目的文件
            write(fd_dest, buf, ret);
        } while (ret > 0);
        // 关闭已打开的文件
        close(fd_src);
        close(fd_dest);
    }
    return 0;
}
