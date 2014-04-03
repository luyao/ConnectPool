/**
 * @file src/connect_pool/simple_connect_pool.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/28 18:10:11
 * @version 1.0 
 * @brief 
 **/


#include "simple_connect_pool.h"

#include <libconfig.h++>
#include <string>
#include <iostream>

#include "checker.h"
#include "class_factory.h"  //for reflection of class
#include "utility.h"

namespace bladecoder_lib { namespace network {

DEFINE_CLASS(SimplePool);
int SimplePool::Init(const libconfig::Setting *root)
{
    ::bladecoder_lib::utility::assert(root, "root node is null");
    using namespace libconfig;
    using std::cerr;
    using std::endl;
    //init the checher
    try{
        const libconfig::Setting &setting = (*root)["Checker"];
        std::string name;
        int duration;
        setting.lookupValue("name", name);
        checker_ = (Checker*)ClassFactory::GetClass(name);
        if (!checker_) {
            cerr<<"The "<<name<<" do not exists"<<endl;
            return -1;
        }
        checker_->Init(root);
    }catch(const SettingNotFoundException &nfex){
        cerr << "No 'Checker' setting in configuration file." << endl;
    }

    //init the dispatcher
    //try{
    //    const libconfig::Setting &setting = (*root)["Dispatcher"];
    //    std::string name;
    //    int duration;
    //    setting.lookupValue("name", name);
    //    checker_ = (Checker*)ClassFactory::GetClass(name);
    //    if (!checker_) {
    //        cerr<<"The "<<name<<" do not exists"<<endl;
    //        return -1;
    //    }
    //    checker_->Init(root);
    //}catch(const SettingNotFoundException &nfex){
    //    cerr << "No 'Checker' setting in configuration file." << endl;
    //}   
    return 0;
}








}}  //end of namespace







/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
