/** 
 * @file connect_pool.cpp
 * @Synopsis  the implementation for the connect pool
 * @author Yao lu
 * @version 1.0
 * @date 2014-03-25
 */

#include "connect_pool.h"

#include <libconfig.h++>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "class_factory.h"     //for reflection of class
#include "connect_pool_impl.h"
#include "utility.h"
#include "net.h"

namespace bladecoder_lib{ namespace network{

Handle::Handle():fd_(0), serv_id_(-1){}

Handle::Handle(int serv_id):fd_(0), serv_id_(serv_id){}

Handle::Handle(const std::string &ip, uint32_t port, int serv_id):
    fd_(0), serv_id_(serv_id), ip_(ip), port_(port){}

{
    
}

Handle::~Handle()
{
    //using namespace bladecoder_lib::network;
    net_close(fd_);
}

int Handle::connect(const std::string &ip, uint32_t port)
{
    int ret = net_connect(ip.c_str(), port);
}

bool Handle::ping()
{
    if (status_ != CONNECTED) return false;
    return net_ping(fd_, ip_.c_str(), port_);
}

class Checker{};
class Dispatcher{};

ConnectPool::ConnectPool():pImpl_(NULL){}

//TODO using log liberary
int ConnectPool::Init(const char *filePath)
{
    using namespace std;
    using namespace libconfig;

    Config cfg;

    int ret = init_config(filePath, cfg);
    if (ret) {
        return -1;
    }

    const Setting &root = cfg.getRoot();
    const Setting *pPoolConfig = NULL;
    string name;
    try {
        cfg.lookupValue("name", name);
        cout << "Connect Pool name: " << name << endl;
        pPoolConfig = &root[name];
        pPoolConfig->lookupValue("PoolType", name);
        cout << "PoolType: " << name << endl;
    }catch(const ::libconfig::SettingNotFoundException &nfex){
        cerr << "No 'name' setting in configuration file." << endl;
    }

    pImpl_ = (ConnectPoolImplIf*)ClassFactory::GetClass(name);
    if (pImpl_) {
        return pImpl_->Init(pPoolConfig);
    }
    return -1;
}


//those functions are very simple, but they cant be inlined, because that will bind
//the implementation to the user.
//So, it's a compromise between performance and flexibility.
Handle ConnectPool::GetHandle()const
{
    return pImpl_->GetHandle();
}

int ConnectPool::FreeHandle(Handle &handle)
{
    return pImpl_->FreeHandle(handle);
}


int ConnectPool::SetChecker(const char *checker)
{
    return pImpl_->SetChecker(checker);
}

const Checker* ConnectPool::GetChecker()const
{
    return pImpl_->GetChecker();
}

int ConnectPool::SetDispatcher(const char *dispatcher)
{
    return pImpl_->SetDispatcher(dispatcher);
}

const Dispatcher* ConnectPool:: GetDispatcher()const
{
    return pImpl_->GetDispatcher();
}



}}//end of namespace bladecoder_lib::network

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
