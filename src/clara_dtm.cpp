/*
 * clara_dtm.cpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * created: 2013-06-12
 * license: BSD
 */
#include <cstdlib>          // exit status

#include "clara/dtm.hpp"

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" file_in.dtm file_out.tif"<<std::endl;
        return EXIT_FAILURE;
    }
    clara::dtm obj;
    obj.load(argv[1]);
    obj.save(argv[2]);
    return EXIT_SUCCESS;
}

