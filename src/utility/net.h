/**
 * @file net.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/04/03 15:17:37
 * @version 1.0 
 * @brief 
 **/



#ifndef  __NET_H_
#define  __NET_H_

#include <string>
#include <stdint.h>       //for uint32_t

namespace bladecoder_lib { namespace network {

int  net_socket(int family, int type, int protocol, bool block=true);

int  net_connect(const char *ip, uint32_t port, uint32_t timeout);

void net_close(int fd);

int  net_ping(int fd, const char *ip, uint32_t port);

}}  //end of namespace




#endif  //__NET_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
