#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int shared_num=0;
void* pthread_test(void* arg)
{
    int tmp=shared_num+1;
    shared_num=tmp;
    return NULL;
}

int main()
{
    pthread_t pthread_id[10000];
    for(int i=0;i<10000;i++)
    {
        pthread_create(&pthread_id[i],NULL,pthread_test,NULL);

    }
    for(int i=0;i<10000;i++)
    {
        pthread_join(pthread_id[i],NULL);
    }

    printf("shared_num=%d\n",shared_num);
    return 0;
}