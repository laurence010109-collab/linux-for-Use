#include<stdio.h>

int main()
{
    open("nihao.txt","r");
    perror("open nihao.txt");
    return 0;
}