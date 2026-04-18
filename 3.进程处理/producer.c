#include <time.h>   // clock_gettime struct timespec
#include <mqueue.h> // mq_open mq_timedsend mq_timedreceive mq_close mq_unlink
#include <stdio.h>  // perror printf
#include <unistd.h> // read STDIN_FILENO
#include <stdlib.h> // exit EXIT_FAILURE
#include <string.h> 
#include<fcntl.h> // O_CREAT O_RDWR O_RDONLY O_NONBLOCK
#include<sys/stat.h> // mode_t

int main()
{
    struct mq_attr attr;//属性队列属性结构体
    attr.mq_flags=0;//标记，默认值为0
    attr.mq_maxmsg=10;//队列可以容纳的消息的最大数量
    attr.mq_curmsgs=0;
    attr.mq_msgsize=100;
    char* mq_name="/p_c_mq";
    mqd_t mqdes=mq_open(mq_name,O_RDWR|O_CREAT,0664,&attr);
    if(mqdes==(mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    char writebuf[100];
    struct timespec time_info;
    while(1)
    {
        clock_gettime(0,&time_info);
        time_info.tv_sec+=5;//设置绝对时间节点为当前时间的5秒后
        memset(writebuf,0,sizeof(writebuf));
        ssize_t read_number=read(STDIN_FILENO,writebuf,sizeof(writebuf));
        if(read_number==-1)
        {
            perror("read");
            continue;
        }
        else if(read_number==0)
        {
            printf("read EOF\n");
            char eof=EOF;
            //当生产者端读到EOF时，向消息队列发送一个特殊的消息，通知消费者端退出
            if(mq_timedsend(mqdes,&eof,sizeof(eof),0,&time_info)==-1)
            {
                perror("mq_timedsend");
            }
            break;  
        }
        
        if(mq_timedsend(mqdes,writebuf,strlen(writebuf),0,&time_info)==-1)
        {
            perror("mq_timedsend");
        }
        printf("从命令行接收到数据，已发送至消费者端\n");
    }
    mq_close(mqdes);
    // mq_unlink 只应调用一次，我们选择在消费者中完成此操作
    // mq_unlink(mq_name);
    return 0;
}