//
// Created by root on 9/27/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <zconf.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <sys/select.h>



void str_cli(FILE* fp, int sd){
    char sendline[1024], recvline[1024];
    while(fgets(sendline, 1024, fp)!=NULL){
        write(sd, sendline, strlen(sendline));
        if(read(sd, recvline, 1024) == 0){
            perror("read error\n");
            return ;
        }
        fputs(recvline, stdout);
    }
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc != 2){
        printf("usage: tcpcli,IPaddress>");
        return -1;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(19000);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
}
