#include<stdio.h>

int main()
{
    fopen("buzhidao.txt","r");
    perror("file open");
    return 0;
}