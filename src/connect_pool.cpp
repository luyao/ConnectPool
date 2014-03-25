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

#include "class_factory.h"  //for reflection of class

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

    virtual int Init(const char *filePath){return 0;}

    virtual Handle GetHandle()const{return Handle(0);}

    virtual int FreeHandle(Handle &handle){return 0;}

    virtual int SetChecker(const Checker *checker){return 0;}

    virtual const Checker* GetChecker()const{return NULL;}

    virtual int SetDispatcher(const Dispatcher *dispatcher){return 0;}

    virtual const Dispatcher* GetDispatcher()const{return NULL;}
};

DEFINE_CLASS(SimplePool);


ConnectPool::ConnectPool():pImpl_(NULL){}

//thos functions are very simple, but they cant be inlined, because that will bind
//the implementation to the user.
//So, it's a compromise between performance and flexibility.
int ConnectPool::Init(const char *filePath)
{
    using namespace libconfig;
    using namespace std;
    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try{
        cfg.readFile(filePath);
    }catch(const FileIOException &fioex){
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }catch(const ParseException &pex){
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
            << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }

    // Get the store name.
    try {
        string name = cfg.lookup("name");
        cout << "Store name: " << name << endl << endl;
    }catch(const SettingNotFoundException &nfex){
        cerr << "No 'name' setting in configuration file." << endl;
    }

    pImpl_ = (ConnectPoolImplIf*)ClassFactory::GetClass("SimplePool");
    return pImpl_->Init(filePath);
}

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
