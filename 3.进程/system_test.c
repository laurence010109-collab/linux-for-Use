#include<stdio.h>
#include<stdlib.h>

int main()
{
    int system_result=system("ping -c 100 www.baidu.com");
    if(system_result!=0)
    {
        printf("无法执行此命令");
        perror("system");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}