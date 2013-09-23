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
#include <libregionMap.h>   // for REGION_MAP

#include "clara/region.hpp"

namespace clara {

using namespace std;

int region::load(const string& filepath, uint8_t format)
{
    REGION_MAP* data = rMap_createMap();
    FILE* file = fopen(filepath.c_str(), "r");

    if ( file == NULL )
        throw runtime_error("[region] could not open file");

    switch (format) {
        case 1:
            if ( rMap_readAsciiMap(file, data) != RMAP_OK ) {
                fclose(file);
                throw runtime_error("[region] could not read ascii map");
            }
            break;
        default:
            throw invalid_argument("[region] unsupported format");
    }

    fclose(file);

    if ( data == NULL )
        throw runtime_error("[region] could not read region");

    io.set_size(N_RASTER, data->nbcol, data->nblig);

    // set UTM zone and transform
    io.set_utm( data->geodesicOrigin.gridZone,
                data->geodesicOrigin.gridZoneDesignation != 0 );
    io.set_transform(
        data->geodesicOrigin.easting,   // top left x
        data->geodesicOrigin.northing,  // top left y
        data->scale,                    // w-e pixel resolution
        data->scale );                  // n-s pixel resolution
    // TODO dig into T3D origin2corner (libregionMap.h:182)
    //io.set_custom_origin(data->origin2corner.wtf_x, data->origin2corner.wtf_y);

    RMAP_REGION* region = data->regions;
    for (int id_class, idx = 0; idx < (data->nbcol * data->nblig); idx++) {
        for (id_class = 0; id_class < N_RASTER; id_class++) {
            // TODO check state undefined ?
            io.bands[id_class][idx] = region->infos3d.growedProbas[id_class];
        }
        region++;
    }

    rMap_destroyMap(data);

    io.bands_name = {"NO_3D_CLASS", "FLAT", "OBSTACLE", "ROUGH", "SLOPE"};

    return EXIT_SUCCESS;
}

} // namespace clara

