#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    if(argc != 2)
    {
        fprintf(stderr,"%s:请填写需要传递的信息\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    if(pipe(pipefd)==-1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);

    }

    pid_t pid=fork();
    if(pid==-1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        //子进程 
        close(pipefd[1]);
        printf("新学员：%d，开始读取\n",getpid());
        char buf[1024];
       while(read(pipefd[0],&buf,1)>0)
        {
            write(STDOUT_FILENO,&buf,1);
        }
        write(STDOUT_FILENO,"\n",1);
        close(pipefd[0]);
        printf("新学员：%d，读取完成\n",getpid());
        exit(EXIT_SUCCESS);    
    }
    else
    {
        //父进程
        close(pipefd[0]);
        printf("老学员：%d，开始写入\n",getpid());
        write(pipefd[1],argv[1],strlen(argv[1]));
        printf("老学员：%d，写入完成\n",getpid());
        close(pipefd[1]);
        waitpid(pid,NULL,0);
        
        exit(EXIT_SUCCESS);

    }

}