#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct Result
{
    char* speak;
    char* speak_len;
}Result;

void* red_thread(void* arg)
{
    Result* result=malloc(sizeof(Result));
    char code=*((char*)arg);
    char* ans=malloc(100);
    while(1)
    {   
        fgets(ans,100,stdin);//从标准输入读取一行文本，存储在ans中，最多读取99个字符（最后一个字符用于存储字符串结束符'\0'）
        if(ans[0]==code)
        {
            free(ans);//释放内存，防止内存泄漏
            printf("红玫瑰离开了!\n");
            
            char* redans=strdup("红玫瑰独自去了纽约.\n");///strcpy
            result->speak=redans;
            result->speak_len=strlen(redans);
            pthread_exit((void*)result);//线程退出，并返回result指针    

        }
        else
        {printf("红玫瑰还在等你!\n");
        }
    }
}

void* white_thread(void* arg)
{
    Result* result=malloc(sizeof(Result));
    char code=*((char*)arg);
    char* ans=malloc(100);
    while(1)
    {
        fgets(ans,100,stdin);
        if(ans[0]==code)
        {
            free(ans);
            printf("白玫瑰离开了!\n");
            char* whiteres=strdup("白玫瑰独自去了伦敦.\n");
            result->speak=whiteres;
            result->speak_len=strlen(whiteres);
            pthread_exit((void*)result);
        }
        else
        {
            printf("白玫瑰还在等你!\n");
        }
    }
}

int main()
{
    char red_code='r';
    char white_code='w';
    pthread_t pid_red;
    pthread_t pid_white;
    Result* red_result;
    Result* white_result;
    pthread_create(&pid_red,NULL,red_thread,&red_code);
    pthread_create(&pid_white,NULL,white_thread,&white_code);
    pthread_join(pid_red,(void**)&red_result);
    printf("红玫瑰故事结局:%s\n",red_result->speak);
    free(red_result->speak);
    free(red_result);
    pthread_join(pid_white,(void**)&white_result);
    printf("白玫瑰故事结局:%s\n",white_result->speak);
    free(white_result->speak);
    free(white_result);
    return 0;
}