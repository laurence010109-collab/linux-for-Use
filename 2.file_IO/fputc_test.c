#include<stdio.h>

int main()
{
    char *file = "io1.txt";
    FILE *IOfile=fopen(file,"a");
    if(IOfile==NULL)
    {
        printf("Error opening file\n");
    }
    else
    {
        printf("file open finish\n");
    }

    int result_fputc=fputc(99,IOfile);
    if(result_fputc==EOF) printf("fputc error\n");
    else printf("fputc finish: %c\n",result_fputc);




    int result=fclose(IOfile);
    if(result==0)
    {
        printf("file close finish\n");
        return 0;
    }
    else if(result==EOF)
    {
        printf("file close error\n");
        return 1;
    }

}