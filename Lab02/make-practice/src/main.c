#include<stdio.h>
#include<fun1.h>
#include<fun2.h>
#include<dylib.h>
int main()
{
	printf("hello world\n");
	fun1();
	fun2();
	dynamic_lib_call();
	return 0;
}
