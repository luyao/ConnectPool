#if 0
~/bin/g++ -std=c++0x  -o `echo $0 |sed -e 's/\..*//'` -g $0
exit
#endif
/**
 * @file test_double_buffered.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/31 15:46:59
 * @version 1.0 
 * @brief 
 **/

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>  //for unordered_map

#include "buffer_mgr.h"

using namespace std;

class A{
public:
    A(){cout<<"new A"<<endl;}
    ~A(){cout<<"delete A"<<endl;}
};

int testScope()
{
    shared_ptr<A> pC(NULL);
    {
        shared_ptr<A> pB(NULL);
        {
            shared_ptr<A> pA(new A);    
            pB = pA;
            pC = pA;
            cout<<"end of A scrop"<<endl;
        }
        cout<<"end of B scrop"<<endl;
    }
    cout<<"end of C scrop"<<endl;
    return 0;
}

int testLifeTime()
{
    shared_ptr<A> pA(new A);    
    shared_ptr<A> pB(pA);
    pA.~shared_ptr();
    cout<<"end of A lifetime"<<endl;
    cout<<"end of B lifetime"<<endl;
    return 0;
}

typedef std::unordered_map<size_t, std::string> Dict;
int load_dict(const void *params, void *data)
{
    if (!params || !data) {
        cout<<"Get Wrong params passed in"<<endl;
        return -1;
    }
    const char *value = static_cast<const char*>(params);
    Dict  *p_dict     = static_cast<Dict *>(data);
    for (size_t i = 2; i<=20; i+=2) {
        p_dict->insert( Dict::value_type(i, value) );
        cout<<"insert:["<<i<<","<<value<<"]"<<endl;
    }
    return 0;
}

int main()
{
    //testScope();
    //testLifeTime();

    Buffer<Dict> dictBuffer(load_dict, "123");
    shared_ptr<Dict> dict = dictBuffer.content();
    if (!dict) {
        cout<<"Get error shared_ptr"<<endl;
        return -1;
    }

    for (auto i=dict->begin(); i != dict->end(); ++i) {
        cout<<i->first<<" "<<i->second<<endl;
    }

    return 0;
}













/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
