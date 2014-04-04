/**
 * @file src/connect_pool/simple_connect_pool.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/28 17:59:08
 * @version 1.0 
 * @brief 
 **/

#ifndef  __SRC_CONNECT_POOL_SIMPLE_CONNECT_POOL_H_
#define  __SRC_CONNECT_POOL_SIMPLE_CONNECT_POOL_H_

#include <list>
#include <vector>               //for vecotr
#include <unordered_map>

#include "class_factory.h"
#include "connect_pool_impl.h"  //for inherience
#include "server.h"


namespace bladecoder_lib{ namespace network{

DECLEAR_CLASS_EX(SimplePool, ConnectPoolImplIf){
public:
    SimplePool(){}

    virtual ~SimplePool(){}

    virtual int Init(const libconfig::Setting *pROot);

    virtual Handle GetHandle()const{return Handle(0);}

    virtual int FreeHandle(Handle &handle){return 0;}

    virtual int SetChecker(const char *checker){return 0;}

    virtual const Checker* GetChecker()const{return NULL;}

    virtual int SetDispatcher(const char *dispatcher){return 0;}

    virtual const Dispatcher* GetDispatcher()const{return NULL;}
protected:
    typedef std::queue<Handle> ConnectionQueue;

    struct ConnectionUnit{
        ConnectionQueue in_use_;
        ConnectionQueue pool_;
    };

    typedef std::unordered_map<Handle, ConnectionUnit> ConnectionDict;

    Checker              *checker_;      //checker for connections, singleton
    Dispatcher           *dispatcher_;   //dispatcher for connections, singleton
    std::vector<Server>  servers_;
    ConnectionDict       connections_;
};




}}  //end of namespace



#endif  //__SRC_CONNECT_POOL_SIMPLE_CONNECT_POOL_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
