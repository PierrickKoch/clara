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

#include "gdalwrap/gdal.hpp"

void color_to_proba(const gdalwrap::raster& band_from,
                          gdalwrap::raster& band_to  ) {
    for (size_t idx = 0; idx < band_to.size(); idx++)
        band_to[idx] = band_from[idx] / 255.0;
}

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" meta.tif rgba.tif region.tif"<<std::endl;
        return EXIT_FAILURE;
    }
    gdalwrap::gdal meta  (argv[1]);
    gdalwrap::gdal rgba  (argv[2]);
    gdalwrap::gdal region;
    region.names = {"NO_3D_CLASS", "FLAT", "OBSTACLE", "ROUGH"};
    region.copy_meta(meta, region.names.size());
    color_to_proba(rgba.bands[0], region.get_band("OBSTACLE")); // red
    color_to_proba(rgba.bands[1], region.get_band("FLAT"));     // green
    color_to_proba(rgba.bands[2], region.get_band("ROUGH"));    // blue

    region.save(argv[3]);

    return EXIT_SUCCESS;
}

