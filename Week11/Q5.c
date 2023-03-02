#include <stdio.h>
#include <string.h>
#include <unistd.h>
void lstFive(char *str)
{
    char *tmp = str;
    int j = 0;
    int length=strlen(tmp);
    for (int i = length - 5; i < length; i++)
    {
        str[j++] = tmp[i];
    }
    str[j] = '\0';
}
int main()
{
    int pipe1[2], pipe2[2]; // pipe1:parent to child     pipe2 : child to parent
    int pid;
    char str1[40] = "Miss Jiaran,I love you so much!";
    char str2[40];
    char readmessage[40];
    int returnstatus1 = pipe(pipe1);
    if (returnstatus1 == -1)
    {
        perror("Unable to create pipe 1 \n");
        return 1;
    }
    int returnstatus2 = pipe(pipe2);
    if (returnstatus2 == -1)
    {
        perror("Unable to create pipe 2 \n");
        return 1;
    }
    pid = fork();
    if (pid != 0)
    {
        close(pipe1[0]); // 关闭不需要的pipe1读取端
        close(pipe2[1]); // 关闭不需要的pipe2写入端
        printf("Parent Write to pipe 1:%s\n", str1);
        write(pipe1[1], str1, sizeof(str1));
        read(pipe2[0], readmessage, sizeof(readmessage));
        printf("Parent Read from pipe 2:%s\n", readmessage);
    }
    else
    {
        close(pipe1[1]); // 关闭不需要的pipe1写入端
        close(pipe2[0]); // 关闭不需要的pipe2读取端
        read(pipe1[0], str2, sizeof(str2));
        printf("In Child: Reading from pipe 1 Message is %s\n", str2);
        lstFive(str2);
        printf("In Child: Writing to pipe 2 Message is the last five bits%s\n", str2);
        write(pipe2[1], str2, sizeof(str2));
    }
    return 0;
}