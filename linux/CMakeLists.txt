PROJECT(Server)

aux_source_directory(. DIR_SRCS)
add_subdirectory(client, sensor, led, net)

add_executable(Server server.cpp)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")