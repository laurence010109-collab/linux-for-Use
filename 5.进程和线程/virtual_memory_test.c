#include<stdio.h>
#include<unistd.h>


int main()
{
    int val=123;
    
    __pid_t pid=fork();
    if(pid<0)
    {
        perror("fork error");
    }
    else if(pid>0)
    {
        sleep(1);
        printf("父进程：val=%d,所在地址为：%p\n",val,&val);
    }
    else
    {   
        //sleep(1);
        val=456;
        printf("子进程：val=%d,所在地址为：%p\n",val,&val);
    }
    return 0;
}