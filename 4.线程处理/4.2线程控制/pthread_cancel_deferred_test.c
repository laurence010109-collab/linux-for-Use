#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_test(void* arg)
{
    printf("这是一个线程!\n");
    printf("线程正在执行...\n");
    sleep(1); // 模拟线程执行的时间
    pthread_testcancel(); // 线程取消点,当线程执行到这里时,如果有取消请求,线程会被取消;如果没有取消请求,线程会继续执行下去
    printf("线程执行结束了!\n");
    return NULL;
    
}


int main()
{
    pthread_t pthread_id;
    void* res;
    pthread_create(&pthread_id,NULL,thread_test,NULL);
    if(pthread_cancel(pthread_id)==0)//取消线程,取消后线程会被强制终止,不需要主线程调用pthread_join来回收资源
    {
        printf("线程取消发送成功!\n");
    }
    else
    {
        printf("线程取消失败!\n");
    }
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