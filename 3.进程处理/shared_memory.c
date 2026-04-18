#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>


int main()
{
    char shmName[100]={0};
    sprintf(shmName,"/letter%d",getpid());

    int fd=shm_open(shmName,O_CREAT|O_RDWR,0666);
    if(fd<0)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(fd,sizeof(shmName));

    char* share=mmap(NULL,sizeof(shmName),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(share==MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    close(fd);
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        strcpy(share,"hello world\n");
        printf("child process write %d\n",getpid());
    }
    else
    {
        waitpid(pid,NULL,0);
        printf("parent process read %d: %s",getpid(),share);
        int ret = munmap(share,sizeof(shmName));
        if(ret<0)
        {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    }



    shm_unlink(shmName);
    return 0;

}