#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{


    char* sem_dress_name="unnamed_shm";
    int sem_fd= shm_open(sem_dress_name,O_CREAT|O_RDWR,0644);
    ftruncate(sem_fd,sizeof(sem_t));
    sem_t* sem=mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED,sem_fd,0);
    sem_init(sem,1,0);
    pid_t pid=fork();
    if(pid==0)
    {
        printf("child process is running ...\n");
        sleep(3);
        sem_post(sem);
    }
    else if(pid>0)
    {
        sem_wait(sem);
        sleep(1);
        printf("parent process is running ...\n");
    }
    else
    {
        printf("fork error!\n");
        exit(1);
    }

    if(pid>0)
    {   
        if(sem_destroy(sem)==-1) perror("sem_destroy error!");
        if(close(sem_fd)==-1) perror("close error!");
        if(munmap(sem,sizeof(sem_t))==-1) perror("munmap error!");
        if(shm_unlink(sem_dress_name)==-1) perror("shm_unlink error!");
        
    }
}