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
    unsigned int local_num = 0x123,network_num=0;
    network_num = htonl(local_num);
    printf("local_num = %#x,network_num = %#x\n",local_num,network_num);
    local_num = ntohl(network_num);
    printf("network_num = %#x,local_num = %#x\n",network_num,local_num);
    
    return 0;
}