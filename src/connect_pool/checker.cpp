/**
 * @file src/connect_pool/checker.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/29 12:53:11
 * @version 1.0 
 * @brief 
 **/


namespace bladecoder_lib { namespace network {

DEFINE_CLASS(Checker);
DEFINE_CLASS(SimpleChecker);


SimpleChecker::SimpleChecker(int duration):duration_(duration){}

/**
 * @brief when reset the cheker, if the checker is running,
 * we should re-running it with new duration
 *
 * @param [in/out] duration   : int
 * @return  void 
 * @retval  0 means sucess 
**/
void SimpleChecker::SetDuration(int duration)
{

}
void SimpleChecker::Run()
{

}






}}











/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
