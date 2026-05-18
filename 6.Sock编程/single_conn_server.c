#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

#define handle_error(cmd,result)\
    if(result<0)    \
    {       \
        perror(cmd);    \
        exit(EXIT_FAILURE);    \
    }


void* read_from_client(void* argv)
{
    int clientfd=*(int*)argv;
    char *read_buf=NULL;
    ssize_t count=0;
    read_buf=malloc(sizeof(char)*1024);
    if(read_buf==NULL)
    {
        perror("malloc");
        return NULL;
    }
    while((count=recv(clientfd,read_buf,1024,0)))
    {
        if(count<0) perror("recv");

        fputs(read_buf,stdout);
    }
    printf("客户端关闭了连接\n");
    free(read_buf);
    return NULL;

}

void* write_to_client(void* argv)
{
    int clientfd=*(int*)argv;
    char*write_buf=NULL;
    ssize_t send_count=0;


    write_buf=malloc(sizeof(char)*1024);
    if(write_buf==NULL)
    {
        printf("malloc");
        shutdown(clientfd,SHUT_WR);
        return NULL;
    }

    while(fgets(write_buf,1024,stdin)!=NULL)
    {
        send_count=send(clientfd,write_buf,1024,0);
        if(send_count<0)
        {
            perror("send");
        }
    }

    printf("服务器关闭了连接\n");
    shutdown(clientfd,SHUT_WR);
    free(write_buf);
    return NULL;

}


int main(int argc,char const* argv[])
{
    int sockfd,clientfd,bind_result,listen_result,accept_result;
    struct sockaddr_in server_addr,client_addr;
    pthread_t pid_read,pid_write;


    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));

    server_addr.sin_family = AF_INET;// IPV4
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);// 监听本地所有IP地址
    server_addr.sin_port=htons(8080);// 监听8080端口

    sockfd=socket(AF_INET,SOCK_STREAM,0);// 创建一个TCP套接字
    handle_error("socket",sockfd);

    bind_result=bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    handle_error("bind",bind_result);

    listen_result=listen(sockfd,2024);// 监听套接字，允许最多2024个连接排队等待接受
    handle_error("listen",listen_result);

    socklen_t client_addr_len=sizeof(client_addr);
    clientfd=accept(sockfd,(struct sockaddr*)&client_addr,&client_addr_len); // 接受一个连接请求，并返回一个新的套接字文件描述符用于与客户端通信
    handle_error("accept",clientfd);

    // 打印客户端的IP地址和端口号，以及与客户端建立连接的套接字文件描述符
    printf("与客户端%s %d建立连接 文件描述符%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),clientfd);
    // 创建两个线程分别处理读写操作
    pthread_create(&pid_read,NULL,read_from_client,(void*)&clientfd);
    pthread_create(&pid_write,NULL,write_to_client,(void*)&clientfd);
    // 等待读写线程结束
    pthread_join(pid_read,NULL);
    pthread_join(pid_write,NULL);

    printf("释放资源\n");
    close(clientfd);
    close(sockfd);
    return 0;

}