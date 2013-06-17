/*
 * dtm.hpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * created: 2013-06-12
 * license: BSD
 */
#ifndef DTM_HPP
#define DTM_HPP

#include <string>

#include "clara/gdal.hpp"

namespace clara {
    /*
     * dtm : from libDTM
     * digital terrain model
     */
    class dtm {
        /* Names of the terrain layers */
        enum {N_POINTS, Z_MAX, Z_MEAN, SIGMA_Z, N_RASTER};
        gdal<N_RASTER> io;
    public:
        int load(const std::string& filepath, const bool ascii);
        inline int save(const std::string& filepath) const {
            return io.save(filepath);
        }
    };
}

#endif // DTM_HPP

