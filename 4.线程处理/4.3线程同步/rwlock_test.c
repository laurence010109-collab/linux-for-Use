#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>


pthread_rwlock_t rwlock;
int shared_data=0;

void* read_thread(void*arg)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("%s read shared_data=%d\n",(char*)arg,shared_data);
    pthread_rwlock_unlock(&rwlock);
    return (void*)0;
}

void* write_thread(void* arg)
{
     pthread_rwlock_wrlock(&rwlock);
    int tmp=shared_data+1;
    
    shared_data=tmp;
    printf("%s write shared_data=%d\n",(char*)arg,shared_data);
    pthread_rwlock_unlock(&rwlock);
    return (void*)0;
}

int main()
{
    pthread_t write1,write2,read1,read2,read3,read4,read5;
    pthread_rwlock_init(&rwlock,NULL);
    pthread_create(&write1,NULL,write_thread,"write1");
   
    pthread_create(&write2,NULL,write_thread,"write2");
    
    pthread_create(&read1,NULL,read_thread,"read1");
    pthread_create(&read2,NULL,read_thread,"read2");
    pthread_create(&read3,NULL,read_thread,"read3");
    pthread_create(&read4,NULL,read_thread,"read4");
    pthread_create(&read5,NULL,read_thread,"read5");
    pthread_join(write1,NULL);
    pthread_join(write2,NULL);
    pthread_join(read1,NULL);
    pthread_join(read2,NULL);
    pthread_join(read3,NULL);
    pthread_join(read4,NULL);
    pthread_join(read5,NULL);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}