#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{

    struct mq_attr attr;//属性队列属性结构体
    attr.mq_flags=0;//标记，默认值为0
    attr.mq_maxmsg=10;//队列可以容纳的消息的最大数量
    attr.mq_msgsize=100;//单条消息的最大允许大小，以字节为单位
    attr.mq_curmsgs=0;//当前队列中的消息数量，对于mq_open，忽略它
    char* mq_name="/father_son_mq";
    mqd_t mqdes=mq_open(mq_name,O_RDWR|O_CREAT,0664,&attr);
    if(mqdes==(mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    pid_t pid=fork();
    if(pid<0)
    {
        //fork失败
        perror("fork");
        exit(EXIT_FAILURE);

    }
    else if(pid==0)
    {
        //子进程 
        char read_buf[100];
        struct timespec time_info;
        for(int i=0;i<10;i++)
        {
            memset(read_buf,0,sizeof(read_buf));
            clock_gettime(0,&time_info);
            time_info.tv_sec+=15;//设置绝对时间节点为当前时间的5秒后
        

            if(mq_timedreceive(mqdes,read_buf,sizeof(read_buf),NULL,&time_info)==-1)
            {
                perror("mq_timedreceive");
            }
            printf("子进程接收消息:%s\n", read_buf);
        }
    }
    else
    {
        //父进程

        char send_buf[100];
        struct timespec time_info;
        for(int i=0;i<10;i++)
        {
            memset(send_buf,0,sizeof(send_buf));
            sprintf(send_buf,"父进程给儿子发送第%d条消息\n",i+1);
            clock_gettime(0,&time_info);
            time_info.tv_sec+=5;//设置绝对时间节点为当前时间的5秒后
        

            if(mq_timedsend(mqdes,send_buf,strlen(send_buf),0,&time_info)==-1)
            {
                perror("mq_timedsend");
            }
            printf("父进程发送消息成功\n");
            sleep(1);//等待子进程结束
        }
    }
    close(mqdes);//关闭队列描述符
    if(pid>0)
    {
        mq_unlink(mq_name);//删除消息队列
    }
    return 0;
}