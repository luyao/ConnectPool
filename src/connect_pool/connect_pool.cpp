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

#include "class_factory.h"  //for reflection of class
#include "utility.h"

namespace bladecoder_lib{ namespace network{

Handle::Handle():fd_(0){}

Handle::Handle(int fd):fd_(fd){}

class Checker{};
class Dispatcher{};

//the declaration of connect pool interface
DECLEAR_INTERFACE(ConnectPoolImplIf ){
public:
    ConnectPoolImplIf(){}

    virtual ~ConnectPoolImplIf(){}

    virtual int Init(const char *filePath)=0;

    virtual Handle GetHandle()const = 0;

    virtual int FreeHandle(Handle &handle)=0;

    virtual int SetChecker(const Checker *checker)=0;

    virtual const Checker* GetChecker()const=0;

    virtual int SetDispatcher(const Dispatcher *dispatcher)=0;

    virtual const Dispatcher* GetDispatcher()const = 0;
};
DEFINE_CLASS(ConnectPoolImplIf);


DECLEAR_CLASS_EX(SimplePool, ConnectPoolImplIf){
public:
    SimplePool(){}

    virtual ~SimplePool(){}

    virtual int Init(const char *filePath);

    virtual Handle GetHandle()const{return Handle(0);}

    virtual int FreeHandle(Handle &handle){return 0;}

    virtual int SetChecker(const Checker *checker){return 0;}

    virtual const Checker* GetChecker()const{return NULL;}

    virtual int SetDispatcher(const Dispatcher *dispatcher){return 0;}

    virtual const Dispatcher* GetDispatcher()const{return NULL;}
};

DEFINE_CLASS(SimplePool);
int SimplePool::Init(const char *filePath)
{
    return 0;
}


ConnectPool::ConnectPool():pImpl_(NULL){}

int ConnectPool::Init(const char *filePath)
{
    using namespace libconfig;
    using namespace std;

    Config cfg;
    int ret = init_config(filePath, cfg);
    if (ret) {
        return -1;
    }

    const Setting &root = cfg.getRoot();
    std::string name;

    try {
        const Setting &connect_pool = root["ConnectPool"];
        connect_pool.lookupValue("PoolType", name);
        cout << "Store name: " << name << endl << endl;
    }catch(const SettingNotFoundException &nfex){
        cerr << "No 'name' setting in configuration file." << endl;
    }

    pImpl_ = (ConnectPoolImplIf*)ClassFactory::GetClass(name);
    return pImpl_->Init(filePath);
}


//thos functions are very simple, but they cant be inlined, because that will bind
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


int ConnectPool::SetChecker(const Checker *checker)
{
    return pImpl_->SetChecker(checker);
}

const Checker* ConnectPool::GetChecker()const
{
    return pImpl_->GetChecker();
}

int ConnectPool::SetDispatcher(const Dispatcher *dispatcher)
{
    return pImpl_->SetDispatcher(dispatcher);
}

const Dispatcher* ConnectPool:: GetDispatcher()const
{
    return pImpl_->GetDispatcher();
}



}}//end of namespace bladecoder_lib::network

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
