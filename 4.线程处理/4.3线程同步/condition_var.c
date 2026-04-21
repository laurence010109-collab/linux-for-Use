#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count=0;

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void* producer(void* arg)
{   
    int item=0;
    pthread_mutex_lock(&mutex);
    while(1)
    {   
        while(count==BUFFER_SIZE)
        {
            pthread_cond_wait(&cond,&mutex);
            
        }
        buffer[count++]=item++;
        printf("Produced: %d\n",buffer[count-1]);
        pthread_cond_signal(&cond);
        
    }
    pthread_mutex_unlock(&mutex);
}

void* consumer(void* arg)
{   
    pthread_mutex_lock(&mutex);
    while(1)
    {
        while(count==0)
        {
            pthread_cond_wait(&cond,&mutex);
            
        }
        printf("Consumed: %d\n",buffer[--count]);
        pthread_cond_signal(&cond);
        
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t producer_thread,consumer_thread;
    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_create(&consumer_thread,NULL,consumer,NULL);
    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);
    return 0;

}