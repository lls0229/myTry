#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/errno.h>

#define     SOCKER_ERROR    -1
#define     CONNECT_ERROR   -2
#define     SEND_ERROR      -3
#define     RECV_ERROR      -4

#define     PORT    9999
#define     MSG     "hello server"

int main() {

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == 0) {
        perror("socket");
        return SOCKER_ERROR;
    }

    struct sockaddr_in c_addr;
    c_addr.sin_family = AF_INET;
    c_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    c_addr.sin_port = htons(PORT);
    socklen_t c_addr_len = sizeof(c_addr);
    int ret = connect(clientfd, (struct sockaddr *)&c_addr, c_addr_len);
    if(ret == -1) {
        perror("connect");
        return CONNECT_ERROR;
    }


    ret = send(clientfd, MSG, strlen(MSG), 0);
    if(ret != strlen(MSG)) {
        perror("send");
        return SEND_ERROR;
    }


    char buf[256] = {0};
    ret = recv(clientfd, buf, strlen(buf), 0);
    if(ret > 0) {
        printf("get msg: %s\n", ret);
    }
    else {
        printf("connect close...\n");
        return RECV_ERROR;
    }

    close(clientfd);


    return 0;
}