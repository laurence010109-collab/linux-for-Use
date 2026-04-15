#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    char* fifo_path = "/tmp/myfifo";
    if(mkfifo(fifo_path, 0666)!=0)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);

    }
    fd=open(fifo_path, O_WRONLY);
    if(fd==-1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    size_t read_size;
    while((read_size=read(STDIN_FILENO, buf, sizeof(buf)))>0)
    {
        write(fd, buf, read_size);
    }
    if(read_size<0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("写入完成\n");
    close(fd);
    return 0;
    
}