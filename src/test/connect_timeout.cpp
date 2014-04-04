#if 0
g++ -o `echo $0 |sed -e 's/\..*//'` -g $0
exit
#endif
/**
 * @file ../test/connect_timeout.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/04/04 11:52:22
 * @version 1.0 
 * @brief 
 **/




#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int fd; 
    struct sockaddr_in addr;
    struct timeval timeo = {0, 0}; 
    socklen_t len = sizeof(timeo);

    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (getsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeo, &len)){
        printf("getsockopt failed\n");
    }else{
        printf("get %d(s) and %d(us)", timeo.tv_sec, timeo.tv_usec);
    }

    if (argc == 4)
        timeo.tv_usec = atoi(argv[3]);

    len = sizeof(timeo);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeo, len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    struct timeval bg, end;
    gettimeofday(&bg, NULL);
    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        if (errno == EINPROGRESS) {
            fprintf(stderr, "timeout\n");
            return -1;
        }       
        perror("connect");
        return 0;
    }       
    printf("connected\n");
    gettimeofday(&end, NULL);
    printf("%u\n", end.tv_usec-bg.tv_usec);

    return 0;
}
















/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
