/*
 * Common LAAS Raster library
 */
#include "clara/clara.hpp"

int clara::dtm::_init_transform(GDALDataset *dataset)
{
    OGRSpatialReference spatial_reference;
    double transform[6] = { 444720, 30, 0, 3751320, 0, -30 };
    char *pszSRS_WKT = NULL;

    dataset->SetGeoTransform( transform );
    spatial_reference.SetUTM( 11, TRUE );
    spatial_reference.SetWellKnownGeogCS( "NAD27" );
    spatial_reference.exportToWkt( &pszSRS_WKT );
    dataset->SetProjection( pszSRS_WKT );
    CPLFree( pszSRS_WKT );
}

int clara::dtm::save_geotiff(string filepath)
{
    GDALDriver *driver;
    GDALDataset *dataset;
    char **options = NULL;
    GDALRasterBand *band;
    this->sizeX = 512;
    this->sizeY = 512;
    GByte raster[this->sizeX * this->sizeY];

    GDALAllRegister();
    driver = GetGDALDriverManager()->GetDriverByName("GTiff");
    if ( driver == NULL ) {
        cerr<<"[GDAL] Could not load GTiff driver"<<endl;
        return 1;
    }

    dataset = driver->Create( filepath.c_str(), 512, 512, 1, GDT_Byte, options );

    band = dataset->GetRasterBand(1);
    band->RasterIO( GF_Write, 0, 0, 512, 512, raster, 512, 512, GDT_Byte, 0, 0 );

    /* Once we're done, close properly the dataset */
    GDALClose( (GDALDatasetH) dataset );

    return 0;
}

int main(int argc, char * argv[])
{
    cout<<"Common LAAS Raster library"<<endl;
    if (argc < 2) {
        cerr<<"usage: "<<argv[0]<<" file.tiff"<<endl;
        return 1;
    }
    clara::dtm obj;
    return obj.save_geotiff(argv[1]);
}

