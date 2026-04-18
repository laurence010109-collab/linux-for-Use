#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int fd=open("io.txt",O_CREAT | O_WRONLY | O_APPEND,0644);
    if(fd==-1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    pid_t pid=fork();
    
    if(pid==-1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        //子进程码
        strcpy(buffer,"child process\n");
    }
    else
    {
        sleep(1);
        //父进程码
        strcpy(buffer,"parent process\n");
    }
    ssize_t bytes_write= write(fd,buffer,strlen(buffer));
    if(bytes_write==-1)
    {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("写入成功\n");
    close(fd);
    if(pid==0)
    {
        printf("子进程退出\n");
    }
    else
    {
        printf("父进程退出\n");
    }
    return 0;
}