/*
 * region.cpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * created: 2013-06-12
 * license: BSD
 */
#include <string>           // for string
#include <stdexcept>        // for runtime_error
#include <cstdlib>          // exit status
#include <cmath>

#include "gladys/gdal.hpp"

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" dsm.dtm dtm.tif"<<std::endl;
        return EXIT_FAILURE;
    }

    gladys::gdal dsm(argv[1]);
    dsm.names = {"Z_MAX"};
    dsm.save(argv[2]);

    return EXIT_SUCCESS;
}

