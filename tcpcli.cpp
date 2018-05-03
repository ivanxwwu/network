//
// Created by root on 10/2/16.
//

#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>

int max(int a,int b)
{
    return a>b?a:b;
}

void str_cli(FILE* fp, int sockfd){
//    int maxfdp1;
//    fd_set rset;
//    FD_ZERO(&rset);
//    char sendline[4096], recvline[4096];
    //send(sockfd, sendline, sizeof(sendline), SO_LINGER);
//    while(fgets(sendline, 4096, fp) != NULL) {
//        write(sockfd, sendline, sizeof(sendline));
//        sleep(1);
//        write(sockfd, sendline, sizeof(sendline));
//        if(read(sockfd, recvline, sizeof(recvline)) == 0){
//            perror("str_cli:server terminated prematurely");
//        }
//        fputs(recvline, stdout);
//    }
//    for(;;){
//        FD_SET(fileno(fp), &rset);
//        FD_SET(sockfd, &rset);
//        maxfdp1 = max(fileno(fp), sockfd) + 1;
//        select(maxfdp1, &rset, NULL, NULL, NULL);
//        if(FD_ISSET(sockfd, &rset)){
//            if(read(sockfd, recvline, 4096) == 0)
//                perror("str_cli:server terminated prematurely");
//            fputs(recvline, stdout);
//        }
//        if(FD_ISSET(fileno(fp), &rset)){
//            if(fgets(sendline, 4096, fp) == NULL){
//                return ;
//            }
//            write(sockfd, sendline, strlen(sendline));
//        }
//    }

    int maxfdp1, stdineof;
    fd_set rset;
    char buf[4096] = {0};
    int n;
    stdineof = 0;
    FD_ZERO(&rset);
    for(;;){
        if(stdineof == 0){
            FD_SET(fileno(fp), &rset);
        }
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(sockfd, &rset)){
            if((n=read(sockfd, buf, 4096))==0){
                if(stdineof == 1){
                    return ;
                }
                else
                    perror("str_cli:server terminated premmature");
            }
            write(fileno(stdout), buf, n);
        }
        if(FD_ISSET(fileno(fp), &rset)){
            if((n=read(fileno(fp), buf, 4096))==0){
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            write(sockfd, buf, n);
        }
    }
}

int main(int argc, char* argv[]){
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    inet_pton(AF_INET, "192.168.163.133", &servaddr.sin_addr);
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0){
        perror("connect fail");
        return 0;
    }
    FILE * fp = fopen("/root/Desktop/CMakeCache.txt", "r+");
    sleep(1);
    str_cli(fp, sockfd);
    fclose(fp);
    exit(0);
}

