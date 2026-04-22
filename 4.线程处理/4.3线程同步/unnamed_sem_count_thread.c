#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *full;// 生产者线程和消费者线程共享的信号量，指向一个无名信号量
sem_t *empty;

int share_num;

int rand_num()
{
    srand(time(NULL));// 使用当前时间作为随机数生成器的种子，以确保每次运行程序时生成不同的随机数
    return rand();
}


void* producer_thread(void* arg)
{
    for(int i=0;i<5;i++)
    {
        sem_wait(empty);// 生产者线程等待empty信号量，确保有空位可用
        printf("\n==========> 第 %d 轮数据传输 <=========\n\n", i + 1);
        sleep(1);// 模拟生产数据的时间
        share_num = rand_num();// 生成一个随机数并存储在共享变量share_num中
        printf("生产者线程生产了数据: %d\n", share_num);
        sem_post(full);// 生产者线程释放full信号量，通知消费者线程有
    }
}

void* consumer_thread(void* arg)
{
    for(int i=0;i<5;i++)
    {
        sem_wait(full);// 消费者线程等待full信号量，确保有数据可用
        printf("消费者线程消费了数据: %d\n", share_num);// 消费者
        sleep(1);// 模拟消费数据的时间
        sem_post(empty);// 消费者线程释放empty信号量，通知生产者线程有空位可用
    }
}

int main()
{
    full=malloc(sizeof(sem_t));
    empty=malloc(sizeof(sem_t));
    // 初始化信号量，full初始值为0，empty初始值为1
    sem_init(full,0,0);
    sem_init(empty,0,1);
    pthread_t producer,consumer;
    pthread_create(&producer,NULL,producer_thread,NULL);
    pthread_create(&consumer,NULL,consumer_thread,NULL);
    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);
    sem_destroy(full);
    sem_destroy(empty);
    free(full);
    free(empty);
    return 0;
}