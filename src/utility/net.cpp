/**
 * @file net.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/04/03 15:19:26
 * @version 1.0 
 * @brief 
 **/

#include "net.h"

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/tcp.h> // for TCP_NODELAY
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

namespace bladecoder_lib { namespace network {


/*
EACCES Permission to create a socket of the specified type and/or protocol is denied.

EAFNOSUPPORT
              The implementation does not support the specified address family.

EINVAL Unknown protocol, or protocol family not available.

EMFILE Process file table overflow.

ENFILE The system limit on the total number of open files has been reached.

ENOBUFS or ENOMEM
Insufficient memory is available.  The socket cannot be created until sufficient resources are freed.

EPROTONOSUPPORT
*/
int net_socket(int family, int type, int protocol, bool block)
{
    int fd = socket(family, type, protocol);
    if (fd <= 0) return fd;  //failed
    if (!block)  return fd;  //using block socket

    //set non-block
    int flags = 0;
    if ( fcntl(fd, F_GETFL, 0) < 0 ) {
        close(fd);
        return -1;
    }

    flags |= O_NONBLOCK;
    if (  fcntl(fd, F_SETFL, flags) < 0 ) {
        close(fd);
        return -1;
    }
    return fd;
}

int net_connect(const char *ip, uint32_t port, int timeout)
{
    fprintf(stdout, "connecting to Server [%s:%d]", ip, port);
    if (NULL == ip) {
        return -1; 
    }   

    //创建tcp套接字
    char str_port[8] = { 0 };
    snprintf(str_port, sizeof(str_port), "%d", port);
    struct addrinfo hints, *res;
    struct timeval time_out = {0, 0};
    int fd = -1; 
    int on = 1;
    int n  = 0;

    bzero(&hints, sizeof(hints));
    hints.ai_family = PF_UNSPEC; // make ipv4 and ipv6 compatible
    hints.ai_socktype = SOCK_STREAM; // use byte stream
    hints.ai_protocol = IPPROTO_TCP; // use tcp
    hints.ai_flags = AI_NUMERICHOST; // use number for ip

    if ( getaddrinfo(ip, str_port, NULL, &res) ) goto connect_fail_free_res;
    if ( ( fd = net_socket(res->ai_family, res->ai_socktype, res->ai_protocol, true) ) < 0) {
        goto connect_fail_free_res;
    }   
    freeaddrinfo(res);

    //set timeout for connect
    time_out.tv_usec= timeout*1000;
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &time_out, sizeof(time_out));

    n = connect(fd, res->ai_addr, res->ai_addrlen);
    if (n < 0) {
        if ( errno == ETIMEDOUT ) {
            fprintf(stderr, "connect(%d,<%d,%s,%d>,%d) call timeout .error[%d] info is %s.",
                    fd, res->ai_family, ip, port, res->ai_addrlen, errno, strerror(errno));
            goto connect_fail;
        }
        else if (errno != EINPROGRESS) {
            fprintf(stderr, "connect(%d,<%d,%s,%d>,%d) call failed.error[%d] info is %s.",
                    fd, res->ai_family, ip, port, res->ai_addrlen, errno, strerror(errno));
            goto connect_fail;
        }
    }
    //cancle the timeout option
    timeout.tv_usec = 0;
    if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        fprintf(stderr, "(setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) ERR(%m)", errno);
    }
    // 设置tcp发送无延迟
    if (setsockopt(fd, IPPROTO_TCP,TCP_NODELAY, &on, sizeof(on)) < 0) {
        fprintf(stderr, "(setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on)) ERR(%m)",errno);
    }
connect_ok:
    return 0;
connect_fail_free_res:
    freeaddrinfo(res);
connect_fail:
    net_close(fd);
    return -1;
}


int net_ping(int fd, const char *ip, uint32_t port)
{
    char buf[1];
    ssize_t ret = recv(fd, buf, sizeof(buf), MSG_DONTWAIT);
    if (ret > 0) {
        fprintf(stderr, "ping: some dirty data pending, error accur! "
                "sock[%d], ip[%s:%d]\n", fd, ip, port);
        return false; 
    } else if (ret == 0) {
        fprintf(stderr, "ping: connection close by peer! sock[%d], ip[%s:%d]",
                fd, ip, port);
        return false; 
    } else {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {  //connection ok
            fprintf(stdout, "ping: Server [%s:%d] is ok", ip, port);
            return true;
        } else {
            fprintf(stderr, "ping: read error[%d] on sock[%d], Server [%s:%d], "
                    "ERR[%m]", errno, fd, ip, port);
            return false; 
        }   
    }
}


void net_close(int fd)
{
    if (fd > 0) {
        close(fd);
    }
}







}}


/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
