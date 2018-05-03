//
// Created by root on 9/25/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <strings.h>
#include <sys/wait.h>

void socket_test(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("socket");
        return ;
    }
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    if(inet_aton("192.168.163.133", &server.sin_addr) != 1){
        perror("inet error");
        return ;
    }
    if(connect(sock, (struct sockaddr*)&server, (socklen_t)sizeof(server))<0){
        perror("connect fail\n");
        return ;
    }
    char buf[1024*10] = {0};
    memset(buf, 0x31, sizeof(buf));
    printf("%d\n", send(sock, buf, sizeof(buf), 0));
    perror("hello");
    memset(buf, 0, sizeof(buf));
    recv(sock, buf, 4096, 0);
    printf("recv :%s\n", buf);

    sleep(20);
    close(sock);

}


int main (void)
{
    printf("This is parent process:%d\n",getpid());
    pid_t pid;
    socket_test();
    int i;
    for(i=0;i<=100;i++)
    {
        pid=fork();
        if(pid==0||pid==-1)  //子进程或创建进程失败均退出,这里是关键所在
        {
            break;
        }
    }
    if(pid==-1)
    {
        perror("fail to fork!\n");
    }
    else if(pid==0)
    {
        printf("子进程id=%d,其对应的父进程id=%d\n",getpid(),getppid());
        socket_test();
        exit(3);
    }
    else
    {
        printf("父进程id=%d\n",getpid());
        int stat;
        //int pr = wait(&stat);
        int pr = waitpid(-1, &stat, NULL);//WNOHANG | WUNTRACED
        printf("wait:%d\n", pr);
        printf("stat:%d\n", stat);
        if(WIFEXITED(stat)){
            printf("the child %d exit normally\n", pr);
            printf("the return code is %d\n", WEXITSTATUS(stat));
        }
        else{
            printf("the child process %d exit abnormally\n", pr);
        }
    }
    sleep(100);
}


