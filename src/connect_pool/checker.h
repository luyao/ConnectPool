/**
 * @file src/connect_pool/checker.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/29 12:36:17
 * @version 1.0 
 * @brief 
 **/


#ifndef  __SRC_CONNECT_POOL_CHECKER_H_
#define  __SRC_CONNECT_POOL_CHECKER_H_

namespace bladecoder_lib{ namespace network{

DECLEAR_INTERFACE(Checker){
public:
    Checker(){}

    virtual ~Checker(){}

    virtual void SetDuration(int duration);

    virtual void Run();
};

DECLEAR_SINGLETON_CLASS(SimpleChecker){
public:
    SimpleChecker(int duration);
    virtual void SetDuration(int duration);
    virtual void Run();
};


}}









#endif  //__SRC_CONNECT_POOL_CHECKER_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
