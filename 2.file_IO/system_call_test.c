#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int fd=open("io.txt",O_RDONLY);
    if(fd==-1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

/*
    ssize_t read (int __fd, void *__buf, size_t __nbytes);
    int __fd:一个整数,表示要从中读取数据的文件描述符
    void *__buf:一个指向缓冲区的指针,读取的数据将被存放到这个缓冲区中
    size_t __nbytes:一个size_t类型的整数,表示要读取的最大字节数 系统调用将尝试读取最多这么多字节的数据,但实际读取的字节数可能会少于请求的数量
    return: (1) 成功时,read()返回实际读取的字节数 这个值可能小于__nbytes,如果遇到了文件结尾（EOF）或者因为网络读取等原因提前结束读取 
            (2) 失败时,read()将返回-1
*/


/*
    ssize_t write (int __fd, const void *__buf, size_t __n);
    int __fd:一个整数,表示要写入数据的文件描述符
    void *__buf:一个指向缓冲区的指针,写入的数据需要先存放到这个缓冲区中
    size_t __n:一个size_t类型的整数,表示要写入的字节数 write()函数会尝试写入__n个字节的数据,但实际写入的字节数可能会少于请求的数量
    return: (1) 成功时,write()返回实际写入的字节数 这个值可能小于__n,如果写入操作因故提前结束,例如: 磁盘满、网络阻塞等情况 
            (2) 失败时,write()将返回-1
*/
    char buffer[1024];
    ssize_t bytes_read;
    while((bytes_read=read(fd,buffer,sizeof(buffer)))>0)
    {
        write(STDOUT_FILENO,buffer,bytes_read);
    }
    if(bytes_read==-1)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
}