#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    char*argv[]={"/usr/bin/ping","-c","10","www.baidu.com",NULL};
    char*envp[]={"PATH=/usr/bin",NULL};
    int ret=execve(argv[0],argv,envp);
    if(ret==-1)
    {
        perror("execve error");
        exit(EXIT_FAILURE);
    }
    return 0;

}