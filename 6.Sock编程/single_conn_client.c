#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>

#define INADDR_LOCAL 0x84120808

#define handle_error(cmd,result) \
        if(result<0)    \
        {       \
            perror(cmd);    \
            exit(EXIT_FAILURE);    \
        }
       

void* read_from_server(void* argv)
{
    int sockfd=*(int*)argv;
    char* read_buf=NULL;
    ssize_t count=0;

    read_buf=malloc(sizeof(char)*1024);
    if(read_buf==NULL)
    {
        perror("malloc");
        return 0;
    }

    while(count=recv(sockfd,read_buf,1024,0))
    {
        if(count<0) perror("recv");
        fputs(read_buf,stdout);
    }

    printf("服务器关闭了连接\n");
    free(read_buf);
    return 0;

}
void* write_to_server(void* argv)
{
    int sockfd=*(int*)argv;
    char* write_buf=NULL;
    ssize_t send_count=0;

    write_buf=malloc(sizeof(char)*1024);
    if(write_buf==NULL)
    {
        perror("malloc");
        shutdown(sockfd,SHUT_WR);
        return 0;
    }

    while(fgets(write_buf,1024,stdin)!=NULL)
    {
        send_count=send(sockfd,write_buf,1024,0);
        if(send_count<0) perror("send");
    }

    printf("客户端关闭了连接\n");
    shutdown(sockfd,SHUT_WR);
    free(write_buf);
    return 0;
}

int main(int argc,char*argv[])
{
    int sockfd,result_bind,result_connect;
    struct sockaddr_in server_addr,client_addr;
    pthread_t read_thread,write_thread;

    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);


    sockfd=socket(AF_INET,SOCK_STREAM,0);
    handle_error("socket",sockfd);

    // result_bind=bind(sockfd,(struct sockaddr*)&client_addr,sizeof(client_addr));
    // handle_error("bind",result_bind);

    result_connect=connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    handle_error("connect",result_connect);


    pthread_create(&read_thread,NULL,read_from_server,&sockfd);
    pthread_create(&write_thread,NULL,write_to_server,&sockfd);

    pthread_join(read_thread,NULL);
    pthread_join(write_thread,NULL);

    printf("客户端关闭了连接\n");
    close(sockfd);
    return 0;
}