cmake_minimum_required(VERSION 2.8.11)
file(GLOB SOLVER_SOURCES  "./*.cpp")
add_executable(EASolver ${SOLVER_SOURCES})
target_link_libraries(EASolver networkMappingEA ${CMAKE_DL_LIBS})
