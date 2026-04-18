#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

char buf[1024];//全局变量，线程共享

void* input_thread(void* arg)
{   int i=0;
    while(1)
    {   
        char c=fgetc(stdin);
        if(c&&c!='\n')
        {
            buf[i]=c;
            i++;
        }
        if(i>=1024)
        {
            i=0;
        }
    }
}

void* output_thread(void* arg)
{   int i=0;
    while(1)
    {
        if(buf[i])
        {
            fputc(buf[i],stdout);
            fputc('\n',stdout);
            buf[i++]=0;
            if(i>=1024)
            {
                i=0;
            }
        }
        else sleep(1);
    }
}


int main()
{   
    pthread_t pid_input;
    pthread_t pid_output;
    // memset(buf,0,sizeof(buf));//buf=molloc(1024)  //堆区分配内存，返回指针，指向分配的内存首地址
    pthread_create(&pid_input,NULL,input_thread,NULL);
    pthread_create(&pid_output,NULL,output_thread,NULL);
    pthread_join(pid_input,NULL);
    pthread_join(pid_output,NULL);
    // free(buf);//堆区分配的内存需要手动释放，防止内存泄漏
    return 0;
}