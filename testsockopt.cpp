//
// Created by root on 10/17/16.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <netinet/sctp.h>

union val {
    int i_val;
    long l_val;
    struct linger linger_val;
    struct timeval timeval1_val;
} val;

static char strres[128];

static char *sock_str_flag(union val * ptr, int len)
{
    if(len != sizeof(int)){
        snprintf(strres, sizeof(strres), "size(%d) not sizeof(int)*" , len);
    }
    else
        snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off":"on");
    return strres;
}
static char *sock_str_int(union val * ptr, int len){
    if(len != sizeof(int)){
        snprintf(strres, sizeof(strres), "size(%d) not sizeof(int)*" , len);
    }
    else
        snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off":"on");
    return strres;
}
static char *sock_str_linger(union val * ptr, int len){
    if(len != sizeof(linger)){
        snprintf(strres, sizeof(strres), "size(%d) not sizeof(linger)*" , len);
    }
    else
        snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off":"on");
    return strres;
}
static char *sock_str_timeval(union val * ptr, int len){
    if(len != sizeof(timeval)){
        snprintf(strres, sizeof(strres), "size(%d) not sizeof(timeval)*" , len);
    }
    else
        snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off":"on");
    return strres;
}

struct sock_opts {
    const char *opt_str;
    int opt_level;
    int opt_name;
    char *(*opt_val_str)(union val *, int);
} sock_opts[] = {
        {"SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, sock_str_flag}    ,
        {"SO_DEBUG", SOL_SOCKET, SO_DEBUG, sock_str_flag}    ,
        {"SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, sock_str_flag}    ,
        {"SO_ERROR", SOL_SOCKET, SO_ERROR, sock_str_int}    ,
        {"SO_KEEPALIVE", SOL_SOCKET, SO_KEEPALIVE, sock_str_flag}    ,
        {"SO_LINGER", SOL_SOCKET, SO_LINGER, sock_str_linger}    ,
        {"SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, sock_str_flag}    ,
        {"SO_RCVBUF", SOL_SOCKET, SO_RCVBUF, sock_str_int}    ,
        {"SO_SNDBUF", SOL_SOCKET, SO_SNDBUF, sock_str_int}    ,
        {"SO_RCVLOWAT", SOL_SOCKET, SO_RCVLOWAT, sock_str_int}    ,
        {"SO_SNDLOWAT", SOL_SOCKET, SO_SNDLOWAT, sock_str_int}    ,
        {"SO_RCVTIMEO", SOL_SOCKET, SO_RCVTIMEO, sock_str_timeval}    ,
        {"SO_SNDTIMEO", SOL_SOCKET, SO_SNDTIMEO, sock_str_timeval}    ,
        {"SO_REUSEADDR", SOL_SOCKET, SO_REUSEADDR, sock_str_flag}    ,
#ifdef SO_REUSEPORT
        {"SO_REUSEPORT", SOL_SOCKET, SO_REUSEPORT, sock_str_flag}    ,
#else
        {"SO_REUSEPORT", 0, 0, NULL}    ,
#endif
        {"SO_TYPE", SOL_SOCKET, SO_TYPE, sock_str_int}    ,
        //{"SO_USELOOPBACK", SOL_SOCKET, SO_USELOOPBACK, sock_str_flag}    ,
        {"IP_TOS", SOL_SOCKET, IP_TOS, sock_str_int}    ,
        {"IP_TTL", SOL_SOCKET, IP_TTL, sock_str_int}    ,
        //{"IPV6_DONTFRAG", SOL_SOCKET, IPV6_DONTFRAG, sock_str_flag}    ,
        {"IPV6_UNICAST_HOPS", SOL_SOCKET, IPV6_UNICAST_HOPS, sock_str_int}    ,
        {"IPV6_V6ONLY", SOL_SOCKET, IPV6_V6ONLY, sock_str_flag}    ,
        {"TCP_MAXSEG", SOL_SOCKET, TCP_MAXSEG, sock_str_int}    ,
        {"TCP_NODELAY", SOL_SOCKET, TCP_NODELAY, sock_str_flag}    ,
        {"SCTP_AUTOCLOSE", SOL_SOCKET, SCTP_AUTOCLOSE, sock_str_int}    ,
        //{"SCTP_MAXBURST", SOL_SOCKET, SCTP_MAXBURST, sock_str_int}    ,
        {"SCTP_MAXSEG", SOL_SOCKET, SCTP_MAXSEG, sock_str_int}    ,
        {"SCTP_NODELAY", SOL_SOCKET, SCTP_NODELAY, sock_str_flag}    ,
        {NULL, 0, 0, NULL}    ,
};

int main(int argc, char **argv){
    int fd;
    socklen_t len;
    struct sock_opts *ptr;
    for(ptr = sock_opts; ptr->opt_str != NULL; ptr++){
        printf("%s: ", ptr->opt_str);
        if(ptr->opt_val_str == NULL)
            printf("(undefined)\n");
        else{
            switch(ptr->opt_level){
                case SOL_SOCKET:
                case IPPROTO_IP:
                case IPPROTO_TCP:
                    fd = socket(AF_INET, SOCK_STREAM, 0);
                    break;
                case IPPROTO_IPV6:
                    fd = socket(AF_INET6, SOCK_STREAM, 0);
                    break;
                case IPPROTO_SCTP:
                    fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
                    break;
                default:
                    printf("can't create fd for level %d\n", ptr->opt_level);
            }

            len = sizeof(val);
            if(getsockopt(fd, ptr->opt_level, ptr->opt_name, &val, &len) == -1){
                perror("getsockopt error");
            }
            else{
                printf("default = %s\n", (*ptr->opt_val_str)(&val, len));
            }
            close(fd);
        }
    }
    exit(0);
}




