/* 
  Copyright (c) YaoLu(yaolu1103@gmail.com) All Rights Reserved
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  * Neither the name of the copyright holders nor the names of their
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS AND CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

/** 
 * @file connect_pool.h
 * @Synopsis  
 * @author Yao lu
 * @version 
 * @date 2014-03-24
 */

#ifndef  __INCLUDE_CONNECT_POOL_H_
#define  __INCLUDE_CONNECT_POOL_H_

namespace bladecoder_lib{ namespace network{

class Uncopyable 
{
protected:                                     // allow construction
    Uncopyable() {}                            // and destruction of
    ~Uncopyable() {}                           // derived objects...
private:
//TODO: using config.h to set appropriate MACRO
#if __cplusplus > 199711L //using c++0x
    Uncopyable(const Uncopyable&) = delete;             // ...but prevent copying
    Uncopyable& operator=(const Uncopyable&) = delete;
#else
    Uncopyable(const Uncopyable&);             // ...but prevent copying
    Uncopyable& operator=(const Uncopyable&);
#endif
}; 

//forward declaration
class ConnectPoolImplIf;
class Checker;
class Dispatcher;

//Wrapping the description, which provide better portability
class Handle{
public:
    Handle();
    explicit Handle(int fd);
    int operator()();

    //implicit conversion
    operator int();

    //can be use to check if the Handle is good to use
    operator bool();
private:
    int fd_;
};

//the connect pool cant be copied, but can be multi
class ConnectPool : virtual public Uncopyable{
public:
    ConnectPool();

    //using open source configure files
    //the configure file should be double-buffered
    //which can be update dynamicly
    //TODO: 1. buffer
    //      2. configure lib DONE
    int Init(const char *filePath);  

    /** 
     * @Synopsis  This method is used to get the Handle, which is a wrapper of
     * descripter. When we need do some portability, we can just redefine the
     * handle.
     * 
     * @Returns   Handle
     */
    Handle GetHandle()const;

    /** 
     * @Synopsis  Give the handle back to the connect pool, if you obtain the
     * Handle using GetHandle. you must free them with FreeHandle
     * 
     * @Param [in]handle The handle obtained by GetHandle which want to be 
     * released.
     * 
     * @Returns    This function should never fail. But still, 0 means success.
     */
    int FreeHandle(Handle &handle);

    /** 
     * @Synopsis  the cheker for the broken connections.
     * 
     * @Param [in]checker: The checker wanna to be used
     * 
     * @Returns    This function should never fail. But still, 0 means success.
     */
    int SetChecker(const char *checker);

    /** 
     * @Synopsis  Maybe we should remove this method. Seems no use
     * 
     * @Returns   
     */
    const Checker* GetChecker()const;

    /** 
     * @Synopsis  The dispatcher for the GetHandle, default dispatcher using RR
     * to dispatch the handles
     * 
     * @Param [in]Dispatcher The dispatcher wanna to use
     * 
     * @Returns    This function should never fail. But still, 0 means success.
     */
    int SetDispatcher(const char *dispatcher);

    const Dispatcher* GetDispatcher()const;
private:
    ConnectPoolImplIf *pImpl_;
};



#include "connect_pool.inl"


}}//end of namespace

#endif  //__INCLUDE/CONNECT_POOL_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
