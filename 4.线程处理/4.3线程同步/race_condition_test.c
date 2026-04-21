#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_THREADS 20000

void* pthread_test(void* arg)
{
    int* num=(int*)arg;
    (*num)++;
    return (void*)0;
}

int main()
{
    int num=0;
    pthread_t thread_id[NUM_THREADS];
    for(int i=0;i<NUM_THREADS;i++)
    {
        pthread_create(thread_id+i,NULL,pthread_test,&num);
    }
    for(int i=0;i<NUM_THREADS;i++)
    {
        pthread_join(thread_id[i],NULL);
    }
    printf("num=%d\n",num);
    return 0;
}