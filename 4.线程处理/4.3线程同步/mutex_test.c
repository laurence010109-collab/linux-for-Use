#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define NUM_PTHREADS 20000
static pthread_mutex_t counter_mutex=PTHREAD_MUTEX_INITIALIZER;
// 定义一个全局的互斥锁counter_mutex，并使用PTHREAD_MUTEX_INITIALIZER进行静态初始化。这种初始化方式在编译时就完成了，不需要在运行时调用pthread_mutex_init函数来初始化互斥锁。通过这种方式，counter_mutex在程序开始执行时就已经准备好，可以直接使用。
void* pthread_test(void*arg)
{
    int*num=(int*)arg;
    pthread_mutex_lock(&counter_mutex);
    (*num)++;
    pthread_mutex_unlock(&counter_mutex);
    return (void*)0;

}


int main()
{

    int num=0;
    pthread_t thread_id[NUM_PTHREADS];
    for(int i=0;i<NUM_PTHREADS;i++)
    {
        pthread_create(&thread_id[i],NULL,pthread_test,&num);
    }
    for(int i=0;i<NUM_PTHREADS;i++)
    {
        pthread_join(thread_id[i],NULL);
    }
    printf("num=%d\n",num);
    return 0;
}