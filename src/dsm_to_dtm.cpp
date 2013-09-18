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

gladys::gdal dsm_to_dtm(const gladys::gdal& dsm) {
    gladys::gdal dtm;
    dtm.copy_meta(dsm, 4);

    dtm.bands_name = {"N_POINTS", "Z_MAX", "Z_MEAN", "SIGMA_Z"};

    auto& np = dtm.get_band("N_POINTS");
    //auto& np = dtm.bands[0]; // N_POINTS
    np.assign(1, np.size());

    auto& sz = dtm.get_band("SIGMA_Z");
    //auto& sz = dtm.bands[3]; // SIGMA_Z
    sz.assign(0, sz.size());

    dtm.get_band("Z_MAX" ) = dsm.bands[0];
    dtm.get_band("Z_MEAN") = dsm.bands[0];

    return dtm;
}

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" dsm.dtm dtm.tif"<<std::endl;
        return EXIT_FAILURE;
    }

    gladys::gdal dsm(argv[1]);
    dsm.bands_name = {"Z_MAX"};
    dsm.save(argv[2]);

    return EXIT_SUCCESS;
}

