/**
 * @file src/connect_pool/connect_pool_impl.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/28 17:37:53
 * @version 1.0 
 * @brief This file is used to define the connect pool implementation
 **/




#ifndef  __SRC_CONNECT_POOL_CONNECT_POOL_IMPL_H_
#define  __SRC_CONNECT_POOL_CONNECT_POOL_IMPL_H_

#include "class_factory.h"
#include "connect_pool.h"

namespace libconfig{
    class Setting;
};
 

namespace bladecoder_lib{ namespace network{

   
//the declaration of connect pool interface
DECLEAR_INTERFACE(ConnectPoolImplIf ){
public:
    ConnectPoolImplIf();

    virtual ~ConnectPoolImplIf();

    virtual int Init(const libconfig::Setting *pRoot)=0;

    virtual Handle GetHandle()const = 0;

    virtual int FreeHandle(Handle &handle)=0;

    virtual int SetChecker(const char *checker)=0;  //using reflection

    virtual const Checker* GetChecker()const=0;

    virtual int SetDispatcher(const char *dispatcher)=0;

    virtual const Dispatcher* GetDispatcher()const = 0;
};



}}//end of namespace





#endif  //__SRC/CONNECT_POOL/CONNECT_POOL_IMPL_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
