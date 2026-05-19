#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//close
#include<arpa/inet.h>//htonl,htons,ntohl,ntohs
#include<pthread.h>
#include<netinet/in.h>

int main()
{

    printf("10.18.138.14 的16进制表示为 0x%X 0x%X 0x%X 0x%X\n",132,18,8,8);

    // 数据结构
    struct sockaddr_in server_addr;
    struct in_addr server_sin_addr;

    in_addr_t server_in_addr_t;

    memset(&server_addr,0,sizeof(server_addr));
    memset(&server_sin_addr,0,sizeof(server_sin_addr));
    memset(&server_in_addr_t,0,sizeof(server_in_addr_t));
    //错误返回-1 表示255.255.255
    server_in_addr_t=inet_addr("132.18.8.8");//返回值是一个32位的无符号整数，网络字节序
    printf("inet_addr: 0x%X\n",server_in_addr_t);

    inet_aton("132.18.8.8",&server_sin_addr);//返回值是一个整数，非0表示成功，0表示失败
    printf("inet_aton: 0x%X\n",server_sin_addr.s_addr);

    inet_pton(AF_INET,"132.18.8.8",&server_sin_addr);//返回值是一个整数，非0表示成功，0表示失败
    printf("inet_pton: 0x%X\n",server_sin_addr.s_addr);    
    return 0;
}