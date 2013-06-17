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

#include "clara/gdal.hpp"

namespace clara {
    /*
     * region : from regionMap
     */
    class region {
        /* Names of the visual terrain classes */
        enum {NO_TEXTURE_CLASS, GRASS, CONCRETE, GRAVEL, TARMAC, N_RASTER};
        gdal<N_RASTER> io;
    public:
        int load(const std::string& filepath, const uint8_t format);
        inline int save(const std::string& filepath) const {
            return io.save(filepath);
        }
    };
}

#endif // REGION_HPP

