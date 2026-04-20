#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

void* detach_test(void* arg)
{
    printf("这是一个分离线程!\n");
    sleep(2);
    printf("分离线程结束了!\n");
    return NULL;
}


int main()
{   
    pthread_t pthread_id;
    pthread_create(&pthread_id,NULL,detach_test,NULL);
    pthread_detach(pthread_id);//分离线程,分离后线程结束会自动回收资源,不需要主线程调用pthread_join来回收资源
    printf("主线程继续执行...\n");
    sleep(3); // 需要注意的是，pthread_detach不会等待子线程结束，如果在后者执行完毕之前主线程退出，则整个进程退出，子线程被强制终止，因此需要等待足够的时间确保子线程完成自己的任务
    printf("主线程结束了!\n");
    return 0;
}