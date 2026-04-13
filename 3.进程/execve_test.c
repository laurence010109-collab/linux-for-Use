#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    /*exec系列函数  父进程跳转进入一个新进程
    推荐使用execve
    char *__path: 需要执行程序的完整路径名
    char *const __argv[]: 指向字符串数组的指针 需要传入多个参数
        (1) 需要执行的程序命令(同*__path)
        (2) 执行程序需要传入的参数
        (3) 最后一个参数必须是NULL
    char *const __envp[]: 指向字符串数组的指针 需要传入多个环境变量参数
        (1) 环境变量参数 固定格式 key=value
        (2) 最后一个参数必须是NULL
    return: 成功就回不来了 下面的代码都没有意义
            失败返回-1
    int execve (const char *__path, char *const __argv[], char *const __envp[]) 
    */

    char* name="lll";
    printf("我是%s %d,我现在在一楼\n",name,getpid());
    char*args[]={"/media/tssh/data/laurence/linux应用/code/3.进程/erlou",name,NULL};
    char*envs[]={NULL};
    int ret=execve(argv[0],args,envs);
    if(ret==-1)
    {
        perror("execve");
        return -1;
    }
    printf("我是%s %d,我现在在五楼\n",name,getpid());
    return 0;

}