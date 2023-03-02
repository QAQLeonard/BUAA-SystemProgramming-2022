// server.c  code
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
    int msgid, ret, i, len;
    if ((msgid = msgget(0x1234, 0666 | IPC_CREAT)) < 0)
    {
        fprintf(stderr, "open msg %x failed.\n", 0x1234);
        return;
    }
    while (1)
    {
        memset(&buf, 0, sizeof(buf));
        while ((ret = msgrcv(msgid, &buf, sizeof(buf.ctext) + sizeof(buf.pid), 1, 0)) < 0)
        {
            if (errno == EINTR)
                continue;
            return;
        }
        memset(&buf1, 0, sizeof(buf1));

        len = strlen(buf.ctext);
        for (i = 0; i < len; i++)
        {
            if (buf.ctext[i] >= 'A' && buf.ctext[i] <= 'Z')
                buf1.ctext[i] = buf.ctext[i] + 32;
            else if (buf.ctext[i] >= 'a' && buf.ctext[i] <= 'z')
                buf1.ctext[i] = buf.ctext[i] - 32;
            else
                buf1.ctext[i] = buf.ctext[i];
        }
        buf1.mtype = buf.pid;
        while ((msgsnd(msgid, &buf1, strlen(buf1.ctext), 0)) < 0)
        {
            if (errno == EINTR)
                continue;
            return;
        }
    }
}