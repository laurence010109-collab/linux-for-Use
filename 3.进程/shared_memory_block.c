#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

    char shm_name[100]={0};
    sprintf(shm_name,"/letter%d",getpid());
    printf("shm_name: %s\n",shm_name);
    int fd=shm_open(shm_name, O_RDWR | O_CREAT, 0666);
    if(fd==-1)
    {
        printf("shm_open error\n");
        return -1;
    }
    while(1);
    return 0;
}