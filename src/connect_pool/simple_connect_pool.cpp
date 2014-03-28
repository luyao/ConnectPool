/**
 * @file src/connect_pool/simple_connect_pool.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/28 18:10:11
 * @version 1.0 
 * @brief 
 **/


#include "simple_connect_pool.h"

#include <libconfig.h++>

#include "class_factory.h"  //for reflection of class

namespace bladecoder_lib { namespace network {

DEFINE_CLASS(SimplePool);
int SimplePool::Init(const libconfig::Setting *root)
{
    using namespace libconfig;
    (void)root;
    
    return 0;
}








}}  //end of namespace







/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
