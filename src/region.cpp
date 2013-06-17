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
#include <cassert>          // for assert
#include <gdal_priv.h>      // for GDALDataset
#include <ogr_spatialref.h> // for OGRSpatialReference
#include <libregionMap.h>   // for REGION_MAP

#include "clara/clara.hpp"

namespace clara {

using namespace std;

region::region():
    data(NULL)
{}

int region::load_ascii(string filepath)
{
    if (data != NULL)
        rMap_destroyMap((REGION_MAP*)data);
    FILE* file = fopen(filepath.c_str(), "r");
    if ( file == NULL ) {
        cerr<<"[region::load_ascii] could not open: "<<filepath<<endl;
        return 1;
    }
    int result = 0;
    if ( rMap_readAsciiMap(file, data) != RMAP_OK )
        result = 1;
    fclose(file);
    return result;
}

int _init_utm_projection(GDALDataset *dataset, int utm)
{
    OGRSpatialReference spatial_reference;
    char *projection = NULL;

    spatial_reference.SetUTM( utm, TRUE );
    spatial_reference.SetWellKnownGeogCS( "WGS84" );
    spatial_reference.exportToWkt( &projection );
    dataset->SetProjection( projection );
    CPLFree( projection );
    return 0;
}

int region::save_geotiff(string filepath)
{
    assert ( data != NULL );
    GDALDriver *driver;
    GDALDataset *dataset;
    GDALRasterBand *band;

    return 0;
}

} // namespace clara

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" file.region file.tiff"<<std::endl;
        return 1;
    }
    clara::region obj;
    obj.load_ascii(argv[1]);
    obj.save_geotiff(argv[2]);
    return 0;
}

