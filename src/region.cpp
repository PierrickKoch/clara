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

int region::load(const string& filepath, uint8_t format = 1)
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

    io.set_size(N_RASTER, data->nbcol, data->nblig);

    // TODO get proper UTM zone and transform
    io.set_utm(31);
    io.set_transform(0, 0);

    RMAP_REGION* region = data->regions;
    for (int id_class, idx = 0; idx < (data->nbcol * data->nblig); idx++) {
        for (id_class = 0; id_class < N_RASTER; id_class++) {
            // TODO check state undefined ?
            io.bands[id_class][idx] = region->infos3d.growedProbas[id_class];
        }
        region++;
    }

    rMap_destroyMap(data);
    return EXIT_SUCCESS;
}

} // namespace clara

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" file_in.region file_out.tiff"<<std::endl;
        return EXIT_FAILURE;
    }
    clara::region obj;
    obj.load(argv[1]);
    obj.save(argv[2]);
    return EXIT_SUCCESS;
}

