#ifndef  __INCLUDE_CONNECT_POOL_H_
#define  __INCLUDE_CONNECT_POOL_H_

#include <unistd.h>

namespace bladecoder_lib{ namespace network{

inline int Handle::operator()()
{
    return fd_;
}

inline operator bool()
{
    return fd_<=0;
}

inline operator int()
{
    return fd_;
}

inline int Handle::close()
{
    close(fd_);
    fd_ = 0;
}


}}//endof name space bladecoder_lib::network

#endif 

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
