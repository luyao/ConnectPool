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
public:
    Server(const char *ip, uint32_t port, uint32_t weight, uint32_t timeout):
        ip_(ip), port_(port), weight_(weight), current_(0), timeout_(timeout){}

    Server(const std::string &ip, uint32_t port, uint32_t weight):
        ip_(ip), port_(port), weight_(weight), current_(0), timeout_(timeout){}

    Server(Server &&serv){
        ip_     = std::move(serv.ip);
        port_   = serv.port_; 
        weight_ = serv.weight_;
        current_= serv.current_;
        timeout_= serv.timeout_;
    }
protected:
    std::string ip_;
    uint32_t    port_;
    uint32_t    weight_;
    int         current_;  //will be used for dispatcher
    int         timeout_;
};

}}









#endif  //__SRC_CONNECT_POOL_SERVER_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
