/*
 * region.hpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * created: 2013-06-12
 * license: BSD
 */
#ifndef REGION_HPP
#define REGION_HPP

#include <string>

#include "gladys/gdal.hpp"

namespace clara {
    /*
     * region : from regionMap
     */
    class region {
        /* Names of the visual terrain classes */
        enum {NO_3D_CLASS, FLAT, OBSTACLE, ROUGH, SLOPE, N_RASTER};
        gladys::gdal io;
    public:
        int load(const std::string& filepath, uint8_t format);
        int save(const std::string& filepath) const {
            return io.save(filepath);
        }
    };
}

#endif // REGION_HPP

