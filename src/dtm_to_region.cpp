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

#include "clara/dtm.hpp"
#include "clara/region.hpp"
#include "gladys/gdal.hpp"

void flag_obstacle(const gladys::gdal::rasters& dtm, gladys::gdal::rasters& region, size_t p1, size_t p2) {
    if (dtm[clara::dtm::N_POINTS][p2] <= 0) {
        // unknown pixel
        region[clara::region::NO_3D_CLASS][p2] = 1;
        return;
    }
    float diff = std::abs(dtm[clara::dtm::Z_MEAN][p1] - dtm[clara::dtm::Z_MEAN][p2]);
    // if the height between to point is greater than 30cm, set 2nd point as obstacle
    if (diff > 0.3) {
        region[clara::region::OBSTACLE][p2] = 1;
        region[clara::region::FLAT][p2]     = 0;
    } else if (diff > 0.2) {
        region[clara::region::OBSTACLE][p2] = 0.5;
        region[clara::region::FLAT][p2]     = 0.5;
    } else {
        region[clara::region::OBSTACLE][p2] = 0;
        region[clara::region::FLAT][p2]     = 1;
    }
}

gladys::gdal dtm_to_region(const gladys::gdal& dtm) {
    gladys::gdal region;
    region.copy_meta(dtm, clara::region::N_RASTER);

    size_t pose, width = dtm.get_width();
    for (size_t px_x = 0; px_x < width            - 1; px_x++)
    for (size_t px_y = 0; px_y < dtm.get_height() - 1; px_y++) {
        // compute :: Z_MEAN{x1 - x2} > 30cm : P_OBSTACLE = 1
        pose = px_x + px_y * width;
        flag_obstacle(dtm.bands, region.bands, pose, pose + 1);
        flag_obstacle(dtm.bands, region.bands, pose, pose + width);
        flag_obstacle(dtm.bands, region.bands, pose, pose + width + 1);
    }

    region.bands_name = {"NO_3D_CLASS", "FLAT", "OBSTACLE", "ROUGH", "SLOPE"};

    return region;
}

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" file_in.dtm region_out.tif"<<std::endl;
        return EXIT_FAILURE;
    }

    clara::dtm dtm;
    dtm.load(argv[1]);

    const gladys::gdal& region = dtm_to_region( dtm.get_gdal() );
    region.save(argv[2]);

    return EXIT_SUCCESS;
}

