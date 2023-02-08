// #include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<errno.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

#define     SOCKET_ERROR    -1
#define     BIND_EEROR      -2
#define     LISTEN_ERROR    -3
#define     ACCEPT_ERROR    -4
#define     READ_ERROR1     -5
#define     READ_ERROR2     -6

#define     PORT            9999
int main() {

    int ret = 0;
    
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == 0) {
        perror("socket");
        return SOCKET_ERROR;
    }

    struct sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_port = htons(PORT);

    ret = bind(listenfd, (struct sockaddr *)&s_addr, sizeof(s_addr));
    if(ret == -1) {
        perror("bind");
        return -2;
    }

    ret = listen(listenfd, 5);
    if(ret == -1) {
        perror("listen");
        return LISTEN_ERROR;
    }
    int clientfd;
    while(1) {
        struct sockaddr_in c_addr;
        socklen_t c_addr_len = sizeof(c_addr);
        
        int clientfd = accept(listenfd, (struct sockaddr *)&c_addr, &c_addr_len);
        if(clientfd == -1) {
            perror("accept");
            return ACCEPT_ERROR;
        }
        
        char buf[256] = {0};
        int s = read(clientfd, buf, sizeof(buf));
        if(s > 0) {
            printf("get msg: %s\n", buf);
            /* !!!!!!! */
            ret = send(clientfd, buf, strlen(buf), 0);
            if(ret != strlen(buf))
                printf("send data error.\n");
            printf("send msg: %s\n", buf);
        }
        else if (s < 0) {

            return READ_ERROR1;
        }
        else {
            printf("connect close...\n");
            return READ_ERROR2;
        }

        close(clientfd);


    }

    close(listenfd);

    return 0;

}