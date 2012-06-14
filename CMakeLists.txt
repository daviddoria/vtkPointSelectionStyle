cmake_minimum_required(VERSION 2.6)

PROJECT(PointSelectionStyle)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

add_library(PointSelectionStyle
PointSelectionStyle.cpp
PointSelectionStyle2D.cpp
PointSelectionStyle3D.cpp)

ADD_EXECUTABLE(Demo Demo.cpp)
TARGET_LINK_LIBRARIES(Demo ${VTK_LIBRARIES} PointSelectionStyle)
