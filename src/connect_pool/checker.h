/**
 * @file src/connect_pool/checker.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/29 12:36:17
 * @version 1.0 
 * @brief 
 **/


#ifndef  __SRC_CONNECT_POOL_CHECKER_H_
#define  __SRC_CONNECT_POOL_CHECKER_H_

namespace libconfig{
    class Setting;
}

namespace bladecoder_lib{ namespace network{

DECLEAR_INTERFACE(Checker){
public:
    Checker(){}

    virtual int Init(const libconfig::Setting *);
    virtual ~Checker(){}

    virtual void SetDuration(int duration);

    virtual void Run();
};

DECLEAR_SINGLETON_CLASS(SimpleChecker){
public:
    SimpleChecker();
    SimpleChecker(int duration);
    virtual int Init(const libconfig::Setting *);
    virtual void SetDuration(int duration);
    virtual void Run();
private:
    int duration_;
};


}}









#endif  //__SRC_CONNECT_POOL_CHECKER_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
