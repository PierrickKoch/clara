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
#include <cassert>          // for assert
#include <gdal_priv.h>      // for GDALDataset
#include <ogr_spatialref.h> // for OGRSpatialReference
#include <libdtm.h>         // for DTM

#include "clara/clara.hpp"

namespace clara {

using namespace std;

dtm::dtm():
    data(NULL)
{}

int dtm::load_ascii(string filepath)
{
    if (data != NULL)
        destroy_dtm(data);
    FILE* file = fopen(filepath.c_str(), "r");
    if ( file == NULL ) {
        cerr<<"[dtm::load_ascii] could not open: "<<filepath<<endl;
        return 1;
    }
    data = dtm_readAsciiDtm(file);
    fclose(file);
    return 0;
}

int dtm::load_binary(string filepath)
{
    if (data != NULL)
        destroy_dtm(data);
    FILE* file = fopen(filepath.c_str(), "r");
    if ( file == NULL ) {
        cerr<<"[dtm::load_binary] could not open: "<<filepath<<endl;
        return 1;
    }
    data = dtm_readBinaryDtm(file);
    fclose(file);
    return 0;
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

int dtm::save_geotiff(string filepath)
{
    assert ( data != NULL );
    GDALDriver *driver;
    GDALDataset *dataset;
    GDALRasterBand *band;
    int idx;
    const size_t size = data->nblig * data->nbcol;

    // array<vector<float>>
    rasters bands;
    for (auto& band: bands)
        band.resize(size);

    DTM_CELL* cell = data->cells_tab;
    for (idx = 0; idx < size; idx++) {
        bands[N_POINTS][idx] = cell->current_info.nb_points;
        bands[Z_MAX][idx]    = cell->current_info.z_max;
        bands[Z_MEAN][idx]   = cell->current_info.z_moyen;
        bands[SIGMA_Z][idx]  = cell->current_info.sigma_z;
        cell++;
    }

    // get the GDAL GeoTiff driver
    GDALAllRegister();
    driver = GetGDALDriverManager()->GetDriverByName("GTiff");
    if ( driver == NULL ) {
        cerr<<"[GDAL] Could not get the GeoTiff driver"<<endl;
        return 1;
    }

    // create the GDAL GeoTiff dataset (n layers of float32)
    dataset = driver->Create( filepath.c_str(), data->nbcol, data->nblig, N_RASTER,
        GDT_Float32, NULL );
    if ( dataset == NULL ) {
        cerr<<"[GDAL] Could not create GeoTiff (multi-layers float32)"<<endl;
        return 1;
    }

    // set the projection
    _init_utm_projection(dataset, 1);
    double transform[6] = {
        0.0, // upper left pixel position x
        1.0, // pixel width
        0.0, //
        0.0, // upper left pixel position y
        0.0, //
        1.0  // pixel height
        };
    // see GDALDataset::GetGeoTransform()
    dataset->SetGeoTransform( transform );

    for (idx = 0; idx < N_RASTER; idx++) {
        band = dataset->GetRasterBand(idx+1);
        band->RasterIO( GF_Write, 0, 0, data->nbcol, data->nblig, bands[idx].data(),
            data->nbcol, data->nblig, GDT_Float32, 0, 0 );
    }

    // close properly the dataset
    GDALClose( (GDALDatasetH) dataset );
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
    obj.load_ascii(argv[1]);
    obj.save_geotiff(argv[2]);
    return 0;
}

