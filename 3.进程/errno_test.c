#include<stdio.h>
#include<errno.h>

int main()
{
    open("/opt","a+");
    printf("errno: %d\n", errno);
    perror("open");
    return 0;
    
}