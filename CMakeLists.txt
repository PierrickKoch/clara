cmake_minimum_required(VERSION 2.8)

set(PACKAGE_NAME clara)
set(PACKAGE_VERSION "0.1")

# C++11 for GCC 4.6
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Find GDAL ( export GDAL_ROOT=$prefix )
find_package(GDAL)

# RPath management http://www.cmake.org/Wiki/CMake_RPATH_handling
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
endif("${isSystemDir}" STREQUAL "-1")

find_package(PkgConfig)

# find libdtm
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
pkg_check_modules(PC_LIBREGIONMAP REQUIRED libregionMap)
set(LIBREGIONMAP_DEFINITIONS ${PC_LIBREGIONMAP_CFLAGS_OTHER})
find_path(LIBREGIONMAP_INCLUDE_DIR libregionMap.h
    HINTS ${PC_LIBREGIONMAP_INCLUDEDIR} ${PC_LIBREGIONMAP_INCLUDE_DIRS})
find_library(LIBREGIONMAP_LIBRARY NAME regionMap
    HINTS ${PC_LIBREGIONMAP_LIBDIR} ${PC_LIBREGIONMAP_LIBRARY_DIRS} )
set(LIBREGIONMAP_INCLUDE_DIRS ${LIBREGIONMAP_INCLUDE_DIR})
set(LIBREGIONMAP_LIBRARIES ${LIBREGIONMAP_LIBRARY})
##

# find libt3d
pkg_check_modules(PC_LIBT3D REQUIRED t3d)
set(LIBT3D_DEFINITIONS ${PC_LIBT3D_CFLAGS_OTHER})
find_path(LIBT3D_INCLUDE_DIR t3d.h
    HINTS ${PC_LIBT3D_INCLUDEDIR} ${PC_LIBT3D_INCLUDE_DIRS}
    PATH_SUFFIXES t3d)
find_library(LIBT3D_LIBRARY NAME t3d
    HINTS ${PC_LIBT3D_LIBDIR} ${PC_LIBT3D_LIBRARY_DIRS} )
set(LIBT3D_INCLUDE_DIRS ${LIBT3D_INCLUDE_DIR})
set(LIBT3D_LIBRARIES ${LIBT3D_LIBRARY})
##

# find libimages3d
pkg_check_modules(PC_LIBIMAGES3D REQUIRED libimages3d)
set(LIBIMAGES3D_DEFINITIONS ${PC_LIBIMAGES3D_CFLAGS_OTHER})
find_path(LIBIMAGES3D_INCLUDE_DIR libimages3d.h
    HINTS ${PC_LIBIMAGES3D_INCLUDEDIR} ${PC_LIBIMAGES3D_INCLUDE_DIRS})
find_library(LIBIMAGES3D_LIBRARY NAME images3d
    HINTS ${PC_LIBIMAGES3D_LIBDIR} ${PC_LIBIMAGES3D_LIBRARY_DIRS} )
set(LIBIMAGES3D_INCLUDE_DIRS ${LIBIMAGES3D_INCLUDE_DIR})
set(LIBIMAGES3D_LIBRARIES ${LIBIMAGES3D_LIBRARY})
##

# find libgdhe
pkg_check_modules(PC_LIBGDHE REQUIRED gdhe)
set(LIBGDHE_DEFINITIONS ${PC_LIBGDHE_CFLAGS_OTHER})
find_path(LIBGDHE_INCLUDE_DIR GDHE.h
    HINTS ${PC_LIBGDHE_INCLUDEDIR} ${PC_LIBGDHE_INCLUDE_DIRS}
    PATH_SUFFIXES gdhe)
find_library(LIBGDHE_LIBRARY NAME gdhe
    HINTS ${PC_LIBGDHE_LIBDIR} ${PC_LIBGDHE_LIBRARY_DIRS} )
set(LIBGDHE_INCLUDE_DIRS ${LIBGDHE_INCLUDE_DIR})
set(LIBGDHE_LIBRARIES ${LIBGDHE_LIBRARY})
##

# find gladys (for gdal wraper)
pkg_check_modules(PC_LIBGGLADYS REQUIRED gladys)
set(LIBGLADYS_DEFINITIONS ${PC_LIBGLADYS_CFLAGS_OTHER})
find_path(LIBGLADYS_INCLUDE_DIR GLADYS.h
    HINTS ${PC_LIBGLADYS_INCLUDEDIR} ${PC_LIBGLADYS_INCLUDE_DIRS}
    PATH_SUFFIXES gladys)
find_library(LIBGLADYS_LIBRARY NAME gladys
    HINTS ${PC_LIBGLADYS_LIBDIR} ${PC_LIBGLADYS_LIBRARY_DIRS} )
set(LIBGLADYS_INCLUDE_DIRS ${LIBGLADYS_INCLUDE_DIR})
set(LIBGLADYS_LIBRARIES ${LIBGLADYS_LIBRARY})
##

include_directories(include)
include_directories( ${GDAL_INCLUDE_DIRS} )
include_directories( ${LIBDTM_INCLUDE_DIRS} )
include_directories( ${LIBREGIONMAP_INCLUDE_DIRS} )

add_executable( clara_dtm src/clara_dtm.cpp src/dtm.cpp )
target_link_libraries( clara_dtm ${GDAL_LIBRARIES} )
target_link_libraries( clara_dtm ${LIBDTM_LIBRARIES} )
install(TARGETS clara_dtm DESTINATION bin)

add_executable( clara_region src/clara_region.cpp src/region.cpp )
target_link_libraries( clara_region ${GDAL_LIBRARIES} )
target_link_libraries( clara_region ${LIBREGIONMAP_LIBRARIES} )
install(TARGETS clara_region DESTINATION bin)

add_executable( clara_dtm_to_region src/dtm_to_region.cpp src/region.cpp src/dtm.cpp )
target_link_libraries( clara_dtm_to_region ${GDAL_LIBRARIES} )
target_link_libraries( clara_dtm_to_region ${LIBDTM_LIBRARIES} )
target_link_libraries( clara_dtm_to_region ${LIBREGIONMAP_LIBRARIES} )
install(TARGETS clara_dtm_to_region DESTINATION bin)

add_executable( clara_tiff_to_region src/tiff_to_region.cpp )
target_link_libraries( clara_tiff_to_region ${GDAL_LIBRARIES} )
install(TARGETS clara_tiff_to_region DESTINATION bin)
