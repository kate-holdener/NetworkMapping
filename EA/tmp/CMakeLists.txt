cmake_minimum_required(VERSION 2.8.11)
file(GLOB VAL_SOURCES  "./*.cpp")
add_executable(ValChecker ${VAL_SOURCES})
target_link_libraries(ValChecker networkMappingEA ${CMAKE_DL_LIBS})
