/*************************************************************************
    > File Name: L4Q1_0.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2022年10月19日 星期三 19时28分57秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int f1,n;
	int i=0;
	f1=open("L4Q1",O_RDONLY);
	char name[20];
	char buf;
	int temp;
	char sub[]="May the force be with you, ";
	n=read(f1,name,20);
	close(f1);

	f1=open("L4Q1",O_WRONLY|O_TRUNC);
	temp=write(f1,sub,27);
	temp=write(f1,name,n-1);
	buf='!';
	temp=write(f1,&buf,1);
	close(f1);
}
