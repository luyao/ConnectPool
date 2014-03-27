#ifndef  __INCLUDE_CONNECT_POOL_H_
#define  __INCLUDE_CONNECT_POOL_H_

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


}}//endof name space bladecoder_lib::network

#endif 

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
