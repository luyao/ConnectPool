#if 0
g++ -o `echo $0 |sed -e 's/\..*//'` -g $0 && exit
#endif
/**
 * @file utility/utility.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/27 18:21:52
 * @version 1.0 
 * @brief 
 **/


#include <libconfig.h++>
#include <iostream>

int init_config(const char *file_path, libconfig::Config &config)
{
    using namespace libconfig;
    using namespace std;

    // Read the file. If there is an error, report it and exit.
    try{
        config.readFile(file_path);
    }catch(const FileIOException &fioex){
        std::cerr << "I/O error while reading file." << std::endl;
        return -1;
    }catch(const ParseException &pex){
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
            << " - " << pex.getError() << std::endl;
        return -1;
    }
    return 0;
}

















/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
