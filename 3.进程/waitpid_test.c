#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{ 
    int process_status;
    printf("I am parent process\n");
    pid_t pid = fork();
    if(pid<0)
    {
        perror("fork");
        return -1;
    }
    else if (pid==0)
    {
        char *args[]={"/usr/bin/ping","-c","5","www.baidu.com",NULL};
        char* env[]={NULL};
        execve(args[0],args,env);
    }
    else{
        printf("老学员%d等待新学员%d联系\n",getpid(),pid);
        waitpid(pid,&process_status,0);
    }
    printf("老学员%d结束\n",getpid());
    return 0;
}