cmake_minimum_required(VERSION 2.8.11)

file(GLOB SOURCES "./*.cpp")
add_executable(graph_generator ${SOURCES})

