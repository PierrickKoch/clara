cmake_minimum_required(VERSION 2.6)

set(PACKAGE_NAME clara)
set(PACKAGE_VERSION "0.1")

find_package(GDAL)

# find libdtm
find_package(PkgConfig)
pkg_check_modules(PC_LIBDTM REQUIRED libdtm)
set(LIBDTM_DEFINITIONS ${PC_LIBDTM_CFLAGS_OTHER})
find_path(LIBDTM_INCLUDE_DIR libdtm.h
    HINTS ${PC_LIBDTM_INCLUDEDIR} ${PC_LIBDTM_INCLUDE_DIRS})
find_library(LIBDTM_LIBRARY NAME dtm
    HINTS ${PC_LIBDTM_LIBDIR} ${PC_LIBDTM_LIBRARY_DIRS} )
set(LIBDTM_INCLUDE_DIRS ${LIBDTM_INCLUDE_DIR})
set(LIBDTM_LIBRARIES ${LIBDTM_LIBRARY})
##

# find regionmap
find_package(PkgConfig)
pkg_check_modules(PC_LIBREGIONMAP REQUIRED libregionMap)
set(LIBREGIONMAP_DEFINITIONS ${PC_LIBREGIONMAP_CFLAGS_OTHER})
find_path(LIBREGIONMAP_INCLUDE_DIR libregionMap.h
    HINTS ${PC_LIBREGIONMAP_INCLUDEDIR} ${PC_LIBREGIONMAP_INCLUDE_DIRS})
find_library(LIBREGIONMAP_LIBRARY NAME regionMap
    HINTS ${PC_LIBREGIONMAP_LIBDIR} ${PC_LIBREGIONMAP_LIBRARY_DIRS} )
set(LIBREGIONMAP_INCLUDE_DIRS ${LIBREGIONMAP_INCLUDE_DIR})
set(LIBREGIONMAP_LIBRARIES ${LIBREGIONMAP_LIBRARY})
##

include_directories(include)
include_directories( ${GDAL_INCLUDE_DIRS} )
include_directories( ${LIBDTM_INCLUDE_DIRS} )
include_directories( ${LIBREGIONMAP_INCLUDE_DIRS} )

add_executable( test src/clara.cpp )
target_link_libraries( test ${GDAL_LIBRARIES} )
target_link_libraries( test ${LIBDTM_LIBRARIES} )
target_link_libraries( test ${LIBREGIONMAP_LIBRARIES} )

