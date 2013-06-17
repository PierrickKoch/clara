/*
 * clara.hpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * created: 2013-06-12
 * license: BSD
 */
#ifndef CLARA_HPP
#define CLARA_HPP

#include <string>
#include <vector>
#include <array>

#include <libdtm.h>         // for DTM
#include <libregionMap.h>   // for REGION_MAP

namespace clara {
    typedef std::vector<float> raster;
    enum {N_POINTS, Z_MAX, Z_MEAN, SIGMA_Z, N_RASTER};
    typedef std::array<raster, N_RASTER> rasters;

    /*
     * dtm : from libDTM
     * digital terrain model
     */
    class dtm {
        DTM* data;
    public:
        dtm();
        int load_ascii(const std::string filepath);
        int load_binary(const std::string filepath);
        int save_geotiff(const std::string filepath);
    };

    /*
     * region : from regionMap
     */
    class region {
        REGION_MAP* data;
    public:
        region();
        int load_ascii(const std::string filepath);
        int save_geotiff(const std::string filepath);
    };
}

#endif // CLARA_HPP

