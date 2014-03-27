/**
 * @file utility/utility.h
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/27 18:21:15
 * @version 1.0 
 * @brief 
 **/


#ifndef  __UTILITY_UTILITY_H_
#define  __UTILITY_UTILITY_H_

namespace libconfig{
    class Config;
}


/* -------------------------------*/
/** 
 * @Synopsis  This function gurrentee that never throw
 * 
 * @Param [in]file_path
 * @Param [in/out]config
 * 
 * @Returns   non-zero  value means failed
 */
/* ---------------------------------*/
int init_config(const char *file_path, libconfig::Config &config);








#endif  //__UTILITY/UTILITY_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
