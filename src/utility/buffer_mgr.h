/**
 * @file buffer_mgr.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/04/01 11:29:57
 * @version 1.0 
 * @brief 
 **/


#ifndef  _____UTILITY_BUFFER_MGR_H_
#define  _____UTILITY_BUFFER_MGR_H_

#include <memory>         //for shared_ptr, only works in c++0x
#include <functional>     //for function template class
#include <queue>          //for priority queue
#include <mutex>          //for mutex and lock_guard

typedef std::function< int(const void *param, void *data) > CreateFn;

//strongly NOT recommand using shared_ptr::get() to SAVE the raw
//pointer.
template<typename T>
class Buffer{
public:
    typedef T                         value_type;
    typedef std::shared_ptr< T >      value_ptr;

    explicit Buffer(const CreateFn &fn):index_(0), creater_(fn){}

    //deprecated, I recommand u use update(), if you use it,
    //You need to check whether the pointer is valid
    Buffer(const CreateFn &fn, const void *params)throw()
        :index_(0),creater_(fn)
    {
        update(params);
    }

    const value_ptr& content()const{return buffer_[getIndex()];}
          value_ptr& content()     {return buffer_[getIndex()];}

    int update(const void *params);

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
int Buffer<T>::update(const void *params)
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
        creater_(params, buffer_[getNextIndex()].get()) ) {
        return -1;  //when loading failed, we donot update the index
    }

    incrIndex();
    return 0;
}


class BufferMgr{
public:
    static BufferMgr& instance()
    {
        static BufferMgr _mgr;
        return _mgr;
    }

    template<typename T>
    int regiesterTimerEvent(const Buffer<T> &buf, int time_out)
    {
        std::lock_guard<std::mutex> lock(lock_);
        queue_.emplace(buf.getCreater(), time_out);
        return 0;
    }

    template<typename T>
    int regiesterFileEvent(const Buffer<T> &buf, const char *file_name,
                           int time_out = DEFAULT_FILE_CHECK_INTERVAL)
    {
        std::lock_guard<std::mutex> lock(lock_);
        queue_.emplace(buf.getCreater(), file_name, time_out);
        return 0; 
    }

    void run()const
    {
        //we calculate the the lowest common denominator first
    }

private:
    static const int DEFAULT_FILE_CHECK_INTERVAL = 10;  //second
    enum{
        STOPPED,
        RUNNING
    };
private:
    BufferMgr():status_(STOPPED){}
    //the buffer unit is sorted by the timeout value
    struct _BufferMgrUnit{
        //create the timer
        _BufferMgrUnit(const CreateFn *fn, int time_out):
            creater_(fn), file_name_(NULL), time_out_(time_out){}

        //create the file monitor which using setted check time
        _BufferMgrUnit(const CreateFn *fn, const char *file_name,int time_out):
            creater_(fn), file_name_(file_name_), time_out_(time_out){}

        const CreateFn *creater_;
        const char     *file_name_;
        int            time_out_;

        bool operator>(const _BufferMgrUnit &rhs)const
        {
            return this->time_out_ > rhs.time_out_;
        }
    };
private:
    std::priority_queue<_BufferMgrUnit,
                        std::vector<_BufferMgrUnit>,
                        std::greater<_BufferMgrUnit> > queue_;
    mutable std::mutex lock_;
    mutable int        status_;  //true means running
};




#endif  //_____UTILITY_BUFFER_MGR_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
