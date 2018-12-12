cmake_minimum_required(VERSION 2.8.11)
project (NETWORK_MAPPING_EA)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(solver)
