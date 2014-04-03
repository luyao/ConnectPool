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


namespace bladecoder_lib { namespace utility{

inline void assert(bool cond, const char *msg)
{
    if ( false == cond ) {
        fprintf(stderr, "%s\n", msg);
        *((int*)3) = 0x3;
    }
}

int gcd(int a,int b){
    if( a < b ){  /*交换两个数，使大数放在a上*/
        return gcd(b, a);
    }else if (a > b) {
        int temp;
        while(b!=0){  /*利用辗除法，直到b为0为止*/
            temp = a%b;
            a=b;
            b=temp;
        }
    }
    return a;  //equal or bigger
}


}}







#endif  //__UTILITY/UTILITY_H_

/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
