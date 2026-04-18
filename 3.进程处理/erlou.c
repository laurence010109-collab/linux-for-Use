#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        printf("参数不够，上不了\n");
        return 1;
    }
    printf("我是%s哥,我的id:%d,上二楼们啊\n",argv[1],getpid());
    return 0;

}