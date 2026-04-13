#include<errno.h>
#include<stdio.h>

int main()
{
    fopen("/opt","a+");
    printf("errno:%d",errno);
    perror("errno_file open");
    return 0;

}