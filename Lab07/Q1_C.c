// client.c  code
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>
#include <unistd.h>
extern int errno;
struct mymsgbuf1
{
    long mtype;
    char ctext[100];
};
struct mymsgbuf
{
    long mtype;
    pid_t pid;
    char ctext[100];
};
void main()
{
    struct mymsgbuf buf;
    struct mymsgbuf1 buf1;
    int msgid, ret;
    pid_t pid = getpid();
    if ((msgid = msgget(0x1234, 0666 | IPC_CREAT)) < 0)
    {
        fprintf(stderr, "open msg %x failed.\n", 0x1234);
        return;
    }
    while (1)
    {
        memset(&buf, 0, sizeof(buf));
        printf("Enter some text:");
        scanf("%s", buf.ctext);

        buf.mtype = 1;
        buf.pid = pid;
        while ((msgsnd(msgid, &buf, strlen(buf.ctext) + sizeof(buf.pid), 0)) < 0)
        {
            if (errno == EINTR)
                continue;
            return;
        }
        memset(&buf1, 0, sizeof(buf1));
        while ((ret = msgrcv(msgid, &buf1, sizeof(buf1.ctext), pid, 0)) < 0)
        {
            if (errno == EINTR)
                continue;
            return;
        }
        printf("Receive converted message:%s", buf1.ctext);
        printf("\n");
    }
}
