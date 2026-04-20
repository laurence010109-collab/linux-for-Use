#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


void* pthread_test(void* arg)
{
    printf("这是一个线程!\n");
    //设置线程取消类型为异步取消,当线程执行到这里时,如果有取消请求,线程会被取消;如果没有取消请求,线程会继续执行下去
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);//设置线程取消类型为异步取消,当线程执行到这里时,如果有取消请求,线程会被取消;如果没有取消请求,线程会继续执行下去
    int i=0;
    while(1)
    {
        printf("%d\n",i++);
    }
    printf("线程执行结束了!\n");
    return NULL;
}

int main()
{
    pthread_t pthread_id;
    pthread_create(&pthread_id,NULL,pthread_test,NULL);
    if(pthread_cancel(pthread_id)==0)//取消线程,取消后线程会被强制终止,不需要主线程调用pthread_join来回收资源
    {
        printf("线程取消成功!\n");
    }
    else
    {
        printf("线程取消失败!\n");
    }
    void* res;
    pthread_join(pthread_id,&res);
    if(res==PTHREAD_CANCELED)
    {
        printf("线程被取消了!\n");
    }
    else
    {
        printf("线程正常结束了!\n");
    }
    return 0;
}