cmake_minimum_required(VERSION 3.0)

PROJECT(LED)
add_executable(LED led.cpp)
TARGET_LINK_LIBRARIES(LED wiringPi pthread)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")