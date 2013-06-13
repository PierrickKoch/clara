/*
 * clara.hpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * create:  2013-06-12
 * edit:    2013-06-12
 * license: BSD
 */
#ifndef CLARA_HPP
#define CLARA_HPP

#include <iostream>         // for string
#include <gdal_priv.h>      // for GDALDataset
//#include <cpl_string.h>     // for ?
#include <ogr_spatialref.h> // for OGRSpatialReference
#include <libdtm.h>         // for dtm
#include <libregionMap.h>   // for region

using namespace std;

namespace clara {
    /*
     * dtm : from libDTM
     * dynamic terrain model
     */
    class dtm {
        int sizeX, sizeY;
        int _init_transform(GDALDataset *dataset);
    public:
        int load_ascii(string filepath);
        int load_binary(string filepath);
        int save_geotiff(string filepath);
    };
    /*
     * region : from regionMap
     */
    class region;
}

#endif // CLARA_HPP

