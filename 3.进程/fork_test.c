#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc,char const*argv[])
{
    printf("laurence教Oldman%d打游戏\n",getpid());

    return 0;
}