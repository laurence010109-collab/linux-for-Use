#include<stdio.h>//perror printf
#include<stdlib.h>//exit EXIT_FAILURE
#include<signal.h>//sigaction sigemptyset sigaddset sigprocmask
#include<unistd.h>//sleep
void sigint_handler(int signum)
{
    printf("收到SIGINT信号，正在处理...\n");
    exit(signum);
}

int main()
{
    if(signal(SIGINT,sigint_handler)==SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("你好，小姐姐加WX吗？\n");
        sleep(1);
    }
    return 0;
}