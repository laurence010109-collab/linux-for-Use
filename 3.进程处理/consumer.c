#include<time.h>
#include<mqueue.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    struct mq_attr attr;
    attr.mq_flags=0;
    attr.mq_maxmsg=10;
    attr.mq_msgsize=100;
    attr.mq_curmsgs=0;
    char* mq_name="/p_c_mq";
    mqd_t mqdes=mq_open(mq_name,O_CREAT | O_RDONLY,0664,&attr);
    if(mqdes==-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    char readbuf[100];
    struct timespec time_info;
    while(1)
    {   clock_gettime(0,&time_info);
        time_info.tv_sec+=86400;//设置绝对时间节点为当前时间的24小时后
        memset(readbuf,0,sizeof(readbuf));
        if(mq_timedreceive(mqdes,readbuf,sizeof(readbuf),NULL,&time_info)==-1)
        {
            perror("mq_timedreceive");
            continue;
        }

        if(readbuf[0]==EOF)
        {
            printf("接收到EOF，退出\n");
            break;
        }
        printf("从生产者端接收到数据：\n%s",readbuf);
    }
    mq_close(mqdes);
    if(mq_unlink(mq_name)==-1)
    {
        perror("mq_unlink");
    }

}
