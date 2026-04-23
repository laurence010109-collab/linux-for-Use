#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/mman.h>


int main()
{
    char* sem_name="/name_sem";
    char* shm_name="/name_shm";
    sem_t* sem=sem_open(sem_name,O_CREAT,0644,1);
    int fd=shm_open(shm_name,O_CREAT|O_RDWR,0644);
    ftruncate(fd,sizeof(int));
    int* value=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    *value=0;
    pid_t pid=fork();
    if(pid<0) perror("fork error");
    else if(pid==0)
    {
        sem_wait(sem);
        int tmp=*value+1;
        sleep(1);
        *value=tmp;
        printf("child process: value=%d\n",*value);
        sem_post(sem);
        sem_close(sem);
    }
    else
    {
        waitpid(pid,NULL,0);
        sem_wait(sem);
        int tmp=*value+1;
        sleep(1);
        *value=tmp;
        printf("parent process: value=%d\n",*value);
        sem_post(sem);
        sem_close(sem);

    }
    if(pid>0) 
    {
        munmap(value,sizeof(int));
        shm_unlink(shm_name);
        sem_unlink(sem_name);
    }
    return 0;

}