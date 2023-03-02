#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  pid_t pid,pid0,pid1;
  int status;
  pid = fork();
  if (pid == 0)
  {
    printf("A");
    exit(12);
  }
  else
  {
    pid0=wait(&status);
    pid1=fork();
    if(pid1==0)
    {
      printf("C\n");
      exit(0);
    }
    else
    {
      printf("B");
    }
  }
}
