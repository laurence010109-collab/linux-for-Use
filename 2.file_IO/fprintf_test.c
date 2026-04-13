#include<stdio.h>

int main()
{
    char* filename="io1.txt";
    FILE*IOfile=fopen(filename,"a+");
    if(IOfile==NULL)
    {
        printf("+a不能打开ia不存在的文件\n");
    } 
    else printf("+a成功打开文件\n");


    /*
    FILE *__restrict __stream: 要写入的文件,写在哪里取决于访问模式
    char *__restrict __fmt: 格式化字符串
    ...: 变长参数列表
    return: 成功返回正整数(写入字符总数不包含换行符) 失败返回EOF
    fprintf (FILE *__restrict __stream, const char *__restrict __fmt, ...)
    */
    char*name="laurence";
    int printfR=fprintf(IOfile,"good morning \ngessis\t%s",name);
    if(printfR==EOF) printf("fprintf失败\n");
    else printf("fprintf成功: %d\n",printfR);

    int result=fclose(IOfile);
    if(result==EOF) 
    {
        printf("fclose失败");
        fprintf(stderr,"%s\n",filename);
        return 1;
    }
    else printf("fclose成功\n"); return 0;


}