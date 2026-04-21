#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define NUM_PTHREADS 20000
static pthread_mutex_t counter_mutex=PTHREAD_MUTEX_INITIALIZER;

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