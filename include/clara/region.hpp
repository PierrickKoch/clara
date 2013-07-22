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
     * terrain classes
     */
    class region {
        gladys::gdal io;
    public:
        /* Names of the visual terrain classes */
        enum {NO_3D_CLASS, FLAT, OBSTACLE, ROUGH, SLOPE, N_RASTER};

        int load(const std::string& filepath, uint8_t format = 1);
        int save(const std::string& filepath) const {
            return io.save(filepath);
        }
        const gladys::gdal& get_gdal() const {
            return io;
        }
    };
}

#endif // REGION_HPP

