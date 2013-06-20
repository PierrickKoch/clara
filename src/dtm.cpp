/*
 * dtm.cpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * created: 2013-06-12
 * license: BSD
 */
#include <string>           // for string
#include <stdexcept>        // for runtime_error
#include <libdtm.h>         // for DTM

#include "clara/gdal.hpp"
#include "clara/dtm.hpp"

namespace clara {

using namespace std;

int dtm::load(const string& filepath, bool ascii = true)
{
    DTM* data;
    FILE* file = fopen(filepath.c_str(), "r");

    if ( file == NULL )
        throw runtime_error("[dtm] could not open file");

    if (ascii)
        data = dtm_readAsciiDtm(file);
    else
        data = dtm_readBinaryDtm(file);

    fclose(file);

    io.set_size(data->nbcol, data->nblig);
    // TODO get proper UTM zone and transform
    io.set_utm(31);
    io.set_transform(0, 0);
    DTM_CELL* cell = data->cells_tab;
    for (int idx = 0; idx < (data->nbcol * data->nblig); idx++) {
        // TODO check state undefined ?
        io.bands[N_POINTS][idx] = cell->current_info.nb_points;
        io.bands[Z_MAX][idx]    = cell->current_info.z_max;
        io.bands[Z_MEAN][idx]   = cell->current_info.z_moyen;
        io.bands[SIGMA_Z][idx]  = cell->current_info.sigma_z;
        cell++;
    }

    destroy_dtm(data);
    return 0;
}

} // namespace clara

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" file.dtm file.tif"<<std::endl;
        return 1;
    }
    clara::dtm obj;
    obj.load(argv[1]);
    obj.save(argv[2]);
    return 0;
}

