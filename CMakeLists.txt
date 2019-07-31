cmake_minimum_required( VERSION 2.8 )

project( lucia )

set( CMAKE_BUILD_TYPE "RELEASE" )
set( CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11" )
add_definitions( ${CMAKE_CXX_FLAGS} )

find_package( OpenMP )
if( OPENMP_FOUND) 
  set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" )
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
endif()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package( OpenAL REQUIRED )
include_directories( ${OPENAL_INCLUDE_DIR} )

include_directories( include . )

add_library( lucia feedforward.cpp lucia.cpp main.cpp )

add_executable( Lucia main.cpp )
target_link_libraries( Lucia lucia ${OpenCV_LIBS} ${OPENAL_LIBRARY})
