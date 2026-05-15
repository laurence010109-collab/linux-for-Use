#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


int main()
{
    unsigned short local_num = 0x1234,network_num=0;
    network_num = htons(local_num);
    printf("local_num = %#x,network_num = %#x\n",local_num,network_num);
    local_num = ntohs(network_num);
    printf("network_num = %#x,local_num = %#x\n",network_num,local_num);
    
    return 0;
}