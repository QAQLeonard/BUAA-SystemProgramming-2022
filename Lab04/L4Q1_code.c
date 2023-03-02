#include<stdio.h>
#include<string.h>

int main()
{
	FILE *temp;
	temp = fopen("L4Q1","r");
	char name[20];
	int n;
	n=fread(name,1,20,temp);
	fclose(temp);
	char sub[]="May the force be with you, ";
	temp = fopen("L4Q1","w");
	fwrite(sub,1,27,temp);
	fwrite(name,1,n-1,temp);
	char buf='!';
	fwrite(&buf,1,1,temp);
	fclose(temp);
	return 0;
}
