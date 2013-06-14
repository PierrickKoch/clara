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

namespace clara {
    typedef std::vector<float> raster;
    enum {N_POINTS, Z_MAX, Z_MEAN, SIGMA_Z, N_RASTER};
    typedef std::array<raster, N_RASTER> rasters;

    /*
     * dtm : from libDTM
     * digital terrain model
     */
    class dtm {
        void * data; // DTM
    public:
        dtm();
        int load_ascii(std::string filepath);
        int load_binary(std::string filepath);
        int save_geotiff(std::string filepath);
    };

    /*
     * region : from regionMap
     */
    class region;
}

#endif // CLARA_HPP

