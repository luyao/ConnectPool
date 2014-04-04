/**
 * @file src/connect_pool/server.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/04/03 11:34:45
 * @version 1.0 
 * @brief 
 **/



#ifndef  __SRC_CONNECT_POOL_SERVER_H_
#define  __SRC_CONNECT_POOL_SERVER_H_

namespace bladecoder_lib { namespace network {

class Server{
    std::string ip_;
    uint32_t    port_;
    uint32_t    weight_;
    int         status_;
public:
    enum {
        UN_INITIALIZED, //un-initialized
        CONNECTED,
        UNCONNECTED,    //temprory un-connected
        BROKEN          //means the server is doomed
    };
    Server(const char *ip, uint32_t port, uint32_t weight):
        ip_(ip), port_(port), weight_(weight), status_(UN_INITIALIZED){}
    Server(const std::string &ip, uint32_t port, uint32_t weight):
        ip_(ip), port_(port), weight_(weight), status_(UN_INITIALIZED){}
};

}}









#endif  //__SRC_CONNECT_POOL_SERVER_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
