#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
    FILE*file=fopen("testfile.txt","w");
    if(file==NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    if(setvbuf(file,NULL,_IONBF,0)!=0)// 关闭缓冲区，之后对file的写入将直接写入文件而不经过缓冲区
    {
        perror("setvbuf");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"hello world\n");
    char*argv[]={"/usr/bin/ping","-c","5","www.baidu.com",NULL};
    char*envp[]={NULL};
    //fflush(file);// 刷新缓冲区，确保数据写入文件

    

    execve(argv[0],argv,envp);
    perror("execve");
    exit(EXIT_FAILURE);
}