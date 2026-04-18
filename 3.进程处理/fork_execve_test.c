#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{ 
    char*name="老学员";
    printf("%s %d在一楼学习\n",name,getpid());
    __pid_t pid=fork();
    if(pid==-1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid==0)
    {
        char*newname="新学员";
        char*args[]={"/media/tssh/data/laurence/linux应用/code/3.进程/erlou",newname,NULL};
        char*envs[]={NULL};
        int env=execve(args[0],args,envs);
        if(env==-1)
        {
            perror("execve error");
            exit(1);
        }
        
    }
    else printf("老学员%d邀请完%d之后还是在一楼学习\n",getpid(),pid);
    return 0;
}