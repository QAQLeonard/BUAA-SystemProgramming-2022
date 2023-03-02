#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
int i = 2, prime[35000], j = 0;
void sigHandler(int signalNum)
{
    printf("The nearest prime number:%d\n", prime[j - 1]);
}
int isPrime(int n)
{
    if (n != 2 && n % 2 == 0)
        return 0;
    for (int i = 2; i * i <= n; i = i + 2)
        if (n % i == 0)
            return 0;
    return 1;
}
int main()
{
    signal(SIGINT, sigHandler);
    while (i <= 65535)
    {
        if (isPrime(i))
            prime[j++] = i;
        i++;
        usleep(1000);
    }
    return 0;
}