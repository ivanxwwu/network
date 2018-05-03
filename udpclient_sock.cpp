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
#include <sys/un.h>

int main (void)
{
    int sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sd==-1)perror("socket create fail\n"), exit(-1);
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX,
            strcpy(addr.sun_path, "/root/a.sock");
    int res = connect(sd, (const struct sockaddr*)&addr, sizeof(addr));
    if(res == -1)perror("connect fail\n"), exit(-1);
    while(1){
        write(sd, "hi, boy", strlen("hi, boy"));
        sleep(1);
    }
    close(sd);
}


