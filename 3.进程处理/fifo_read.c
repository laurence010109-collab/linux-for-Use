#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *fifo_path = "/tmp/myfifo";
    int fd =open(fifo_path, O_RDONLY);
    if(fd==-1)
    {
        perror("open");
        exit(1);
    }
    char buf[100];
    size_t read_size;
    while((read_size=read(fd, buf, sizeof(buf)))>0)
   {
        write(STDOUT_FILENO,buf,read_size);
   }
    if(read_size<0)
    {
        perror("read");
        close(fd);
        exit(1);
    }
    printf("读取完成\n");
    close(fd);
    return 0;
}