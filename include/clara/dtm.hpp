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

#include "gdalwrap/gdal.hpp"

namespace clara {
    /*
     * dtm : from libDTM
     * digital terrain model
     */
    class dtm {
        gdalwrap::gdal io;
    public:
        /* Names of the terrain layers */
        enum {N_POINTS, Z_MAX, Z_MEAN, SIGMA_Z, N_RASTER};

        int load(const std::string& filepath, bool ascii = true);
        void save(const std::string& filepath) const {
            io.save(filepath);
        }
        const gdalwrap::gdal& get_gdal() const {
            return io;
        }
    };
}

#endif // DTM_HPP

