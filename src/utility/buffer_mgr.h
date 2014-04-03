/**
 * @file buffer_mgr.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/04/01 11:29:57
 * @version 1.0 
 * @brief 
 **/


#ifndef  _____UTILITY_BUFFER_MGR_H_
#define  _____UTILITY_BUFFER_MGR_H_

#include <chrono>         //for chrono
#include <memory>         //for shared_ptr, only works in c++0x
#include <functional>     //for function template class
#include <queue>          //for priority queue
#include <mutex>          //for mutex and lock_guard
#include <thread>         //for thread
#include <sys/stat.h>
#include <iostream>

#include "utility.h"

typedef std::function< int(void *data) > CreateFn;

//strongly NOT recommand using shared_ptr::get() to SAVE the raw
//pointer.
template<typename T>
class Buffer{
public:
    typedef T                         value_type;
    typedef std::shared_ptr< T >      value_ptr;

    //You need to check whether the pointer is valid
    explicit Buffer(const CreateFn &fn)throw()
        :index_(0),creater_(fn)
    {
        update();
    }

    const value_ptr& content()const{return buffer_[getIndex()];}
          value_ptr& content()     {return buffer_[getIndex()];}

    int update();

    const CreateFn*  getCreater() const{return &creater_;}
    void setCreater(const CreateFn &fn){creater_ = fn;}
private:
    size_t getIndex()    const {return index_;}
    size_t getLastIndex()const {return index_^0x1;}
    size_t getNextIndex()const {return index_^0x1;}
    void   incrIndex()         {index_ ^= 0x1;}
private:
    value_ptr  buffer_[2];
    size_t     index_;  //only take ^ operation
    CreateFn   creater_;
};

template<typename T>
int Buffer<T>::update()
{
    value_ptr &current = buffer_[getNextIndex()];
    //0 means not init yet, 1 means hold by itself
    if (current.use_count() > 1) {
        //we dont have space to hold new data
        //TODO: use queue to solve this problem
        fprintf(stderr,"%s", "We dont have enough space for new data\n"); 
        *(int*)(0x1) = 1;  //core dump at once
    }

    //now the counter of reference is 2, one for the current, and another for 
    //buffer_[getNextIndex()] after calling the assignment operation, the 
    //counter is 1, when the life-time of current is over, the data will be freed
    buffer_[getNextIndex()] = value_ptr( new (std::nothrow) value_type() );
    if (!buffer_[getNextIndex()] ||
        creater_(buffer_[getNextIndex()].get()) ) {
        return -1;  //when loading failed, we donot update the index
    }

    incrIndex();
    return 0;
}

const bool LOVE = true;

class BufferMgr{
public:
    static const BufferMgr& instance()
    {
        static BufferMgr _mgr;
        return _mgr;
    }

    template<typename T>
    int regiesterTimerEvent(Buffer<T> &buf, int time_out)const
    {
        std::thread _thread(
            [&, time_out]{  //the timeout can not be reference
                while( LOVE ) {
                    std::this_thread::sleep_for(std::chrono::seconds(time_out));
                    buf.update();
                }
            }
        );
        _thread.detach();
        return 0;
    }

    template<typename T>
    int regiesterFileEvent(Buffer<T> &buf, const std::string &file_name,
                           int time_out = DEFAULT_FILE_CHECK_INTERVAL)const
    {
        std::thread _thread(
            [&, file_name, time_out]{
                int now = 0;
                while( LOVE ) {
                    std::this_thread::sleep_for(std::chrono::seconds(time_out));
                    struct stat fileStat;
                    if (stat(file_name.c_str(), &fileStat))continue;
                    if (now < fileStat.st_mtime)buf.update();
                    now = fileStat.st_mtime; 
                }
            }
        );
        _thread.detach();
        return 0; 
    }

private:
    static const int DEFAULT_FILE_CHECK_INTERVAL = 1;  //second
};


#endif  //_____UTILITY_BUFFER_MGR_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
