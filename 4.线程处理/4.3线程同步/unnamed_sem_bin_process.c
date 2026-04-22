#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<semaphore.h>

int main()
{
    // 定义一个字符串变量dress_name，表示共享内存对象的名称。在使用shm_open创建共享内存对象时，需要提供一个唯一的名称，以便不同进程能够通过该名称访问同一个共享内存对象。
    char* dress_name="unnamed_sem_shm_dress";
    char* dress_sem_name="unnamed_sem_shm_dress_sem";
    // 创建一个新的共享内存对象，使用shm_open函数，并指定O_CREAT和O_RDWR标志以创建可读写的共享内存对象。权限设置为0644，表示所有者具有读写权限，组用户和其他用户具有只读权限。
    int value_fd=shm_open(dress_name,O_CREAT|O_RDWR,0644);
    
    int sem_fd=shm_open(dress_sem_name,O_CREAT|O_RDWR,0644);
    // 使用ftruncate函数将共享内存对象的大小设置为sizeof(int)，以确保共享内存对象足够大以存储一个整数值。
    ftruncate(value_fd,sizeof(int));
    ftruncate(sem_fd,sizeof(sem_t));
    // 使用mmap函数将共享内存对象映射到当前进程的地址空间，并返回一个指向映射区域起始位置的指针。参数说明如下：
    int* value=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,value_fd,0);
    sem_t* sem=mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED,sem_fd,0);
    printf("value=%d\n",*value);
    *value=0;// 将共享内存中的整数值初始化为0，以便后续的父子进程可以通过这个共享内存来进行通信和数据共享。
    
    sem_init(sem,1,1);// 初始化一个无名信号量，初始值为1，表示资源可用，第二个参数1表示进程间共享
    int pid=fork();
    if(pid==0)
    {   
        sem_wait(sem);
        printf("this is child process start\n");
        int tmp=*value+1;
        //sleep(1);
        *value=tmp;
        printf("this is child process, value=%d\n",*value);
        sem_post(sem);
    }
    else if(pid>0)
    {   
        sem_wait(sem);
        printf("this is father process start\n");
        int tmp=*value+1;
        //sleep(1);
        *value=tmp;
        printf("this is father1 process, value=%d\n",*value);
        sem_post(sem);
        waitpid(pid,NULL,0);
        printf("this is father2 process, value=%d\n",*value);
        
    }
    else
    {
        perror("fork error\n"); 
    }
    
    // 解除内存映射
    if(munmap(value,sizeof(int))==-1) perror("munmap error");
    if(munmap(sem,sizeof(sem_t))==-1) perror("munmap error");
    // 关闭文件描述符和删除共享内存对象
    if(close(value_fd)==-1) perror("close error");
    if(close(sem_fd)==-1) perror("close error");
    // 删除共享内存对象，释放资源
    if(pid>0)
    {
        if(shm_unlink(dress_name)==-1) perror("shm_unlink error");
        if(shm_unlink(dress_sem_name)==-1) perror("shm_unlink error");
    }

     return 0;
}