#include<stdio.h>
#include<stdlib.h>

int main()
{

    char* ch=malloc(10);
    /*
    stdin: 标准输入FILE *
    */
    fgets(ch,10,stdin);
    printf("helle: %s\n",ch);
    /*
    stdout: 标准输出FILE * 写入这个文件流会将数据输出到控制台
    printf底层就是使用的这个
    */

    /*
    写入文件一个字符串
    char *__restrict __s: 需要写入的字符串
    FILE *__restrict __stream: 要写入的文件,写在哪里取决于访问模式
    return: 成功返回非负整数(一般是0,1) 失败返回EOF
    int fputs (const char *__restrict __s, FILE *__restrict __stream)
    */
    fputs(ch,stdout);

    fputs(ch,stderr);
    return 0;
}