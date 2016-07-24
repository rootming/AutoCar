cmake_minimum_required(VERSION 3.0)
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

PROJECT(Server)

set(SRC_PART_DIR base motor)
aux_source_directory(. DIR_SRCS)
include_directories(${SRC_PART_DIR})
add_subdirectory(base)
add_subdirectory(motor)
link_directories(${SRC_PART_DIR})

add_executable(Server ${DIR_SRCS})
TARGET_LINK_LIBRARIES(Server motor_lib base_lib wiringPi pthread m)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11")

# include(CheckCXXCompilerFlag)

# if(COMPILER_SUPPORTS_CXX11)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# elseif(COMPILER_SUPPORTS_CXX0X)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
# else()
#         message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
# endif()