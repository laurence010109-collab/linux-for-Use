#include<stdio.h>

int main()
{
    FILE*IOfile=fopen("io1.txt", "r");
    if(IOfile==NULL) printf("文件读取失败\n");
    /*
    FILE *__stream: 需要读取的文件
    return： 读取的一个字节 到文件结尾或出错返回EOF
    int fgetc (FILE *__stream)
    */
    int fget_result=fgetc(IOfile);
    while(fget_result!=EOF)
    {
        printf("%c", fget_result);
        fget_result=fgetc(IOfile);
    }
    
    int fclose_result=fclose(IOfile);
    if(fclose_result!=0)
    {
        printf("文件关闭失败\n");
        return -1;
    }
    return 0;
}