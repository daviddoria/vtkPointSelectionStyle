cmake_minimum_required(VERSION 2.6)

PROJECT(PointSelectionStyle)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(Demo Demo.cpp
PointSelectionStyle.cpp
PointSelectionStyle2D.cpp
PointSelectionStyle3D.cpp
)

TARGET_LINK_LIBRARIES(Demo ${VTK_LIBRARIES})
