#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t unnamed_sem; // 定义一个无名信号量，注意它是全局变量，因此在所有线程中都可见
int shared_num=0;
void* pthread_test(void* arg)
{   // 进入临界区之前，调用sem_wait()函数等待信号量可用。当信号量的值大于0时，sem_wait()会将其值减1并立即返回，允许线程进入临界区；如果信号量的值为0，则线程将被阻塞，直到其他线程调用sem_post()释放资源并将信号量的值增加到大于0。
    sem_wait(&unnamed_sem);
    int tmp=shared_num+1;
    shared_num=tmp;
    // 离开临界区之前，调用sem_post()函数释放信号量。sem_post()会将信号量的值增加1，如果有其他线程正在等待该信号量，则会唤醒其中一个线程，使其能够继续执行。
    sem_post(&unnamed_sem);
    return NULL;
}

int main()
{
    sem_init(&unnamed_sem,0,1);// 初始化一个无名信号量，初始值为1，表示资源可用，第二个参数0表示线程间共享
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
    sem_destroy(&unnamed_sem);// 销毁无名信号量，释放资源
    return 0;
}