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

#include <iostream>
#include <memory>         //for shared_ptr, only works in c++0x
#include <functional>     //for function template class
#include <unordered_map>  //for unordered_map

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
}

typedef function< int(void *param, void *data) > CreateFn;

//all data wanna to use double-buffer should inherence from this class,
//call load to load new data,
//use valid to check if data can be used
//this class should have a default constructor
template<typename T>
class BufferedData {
public:
    //we dont provide the copy construct for T
    BufferedData():valid_(false){}
    BufferedData(CreateFn fn):valid_(false), creater_(fn){}

    void     setCreater(CreateFn fn){creater_ = fn;}
    CreateFn getCreater()const      {return creater_;}

    int  load(const void *params)
    {
        if ( !creater_(params, &data_) ){
            valid_ = true;
            return 0;
        }
        return -1;
    }

    bool valid()const{return valid_;}

    T* get()
    { 
        if(valid_)return &data_;
        return NULL;
    }

    const T* get()const
    {
        if(valid_)return &data_;
        return NULL;
    }
private:
    T           data_;
    bool        valid_;
    CreateFn    creater_;
};


template<typename T>
class Buffer{
public:
    typedef BufferedData<T>                    value_type;
    typedef shared_ptr< BufferedData<T> >      value_ptr;

    Buffer():index_(0){}

    explicit Buffer(CreateFn fn):index_(0)
    {
        buffer_[getIndex()] = value_ptr(new (std::nothrow)(value_type));
        if (buffer_[getIndex()].get()) {
            buffer_[getIndex()]->setCreater(fn);
        }
    }

    Buffer(CreateFn fn, const void *params)throw():index_(0)
    {  //deprecated, I recommand u use update()
        buffer_[getIndex()] = value_ptr(new (std::nothrow)(value_type));
        if (buffer_[getIndex()].get()) {
            buffer_[getIndex()]->setCreater(fn);
        }
        if (buffer_[getNextIndex()]->load(params) ) {
            exit(-1);
        }
    }

    value_ptr& content()
    {
        return buffer_[getIndex()];
    }

    T* get()
    {
        return buffer_[getIndex()].get();
    }

    const T* get()const
    {
        return buffer_[getIndex()].get();
    }

    int update(const void *params)
    {
        value_ptr &current = buffer_[getNextIndex()];
        //0 means not init yet, 1 means hold by itself
        if (current.use_count() == 0) {
            ;  //do nothing
        }else if (current.use_count() == 1) {
            current.~shared_ptr();  //this will call deleter
        }else{  //we dont have space to hold new data
            //TODO: use queue to solve this problem
            fprintf(stderr,"%s", "We dont have enough space for new data\n"); 
            *(int*)(0x1) = 1;  //core dump at once
        }

        buffer_[getNextIndex()] = new (std::nothrow) value_type();
        if (buffer_[getNextIndex()].get() && 
            buffer_[getNextIndex()]->load(params)) {
            return -1;  //loading failed means we need to use old data
        }

        //after new the data, we update the index
        incrIndex();
        return 0;
    }
private:
    size_t getIndex()const{return index_;}
    size_t getLastIndex()const{return index_^0x1;}
    size_t getNextIndex()const{return index_^0x1;}
    void   incrIndex(){index_ ^= 0x1;}

    value_ptr  buffer_[2];
    size_t index_;  //only take ^ operation
};

typedef std::unordered_map<size_t, std::string> Dict;
int load_dict(const void *params, void *data)
{
    if (!params || !data) {
        return -1;
    }
    const char *value = static_cast<const char*>(params);
    Dict  *p_dict     = static_cast<Dict *>(data);
    for (size_t i = 2; i<=20; i+=2) {
        p_dict->insert( Dict::value_type(i, value) );
    }
    return 0;
}


class BufferMgr{
public:

};

int main()
{
    testScope();
    testLifeTime();
    Buffer<Dict> dictBuffer(load_dict);
    //shared_ptr<Dict> dict = dictBuffer.content();

    return 0;
}













/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
