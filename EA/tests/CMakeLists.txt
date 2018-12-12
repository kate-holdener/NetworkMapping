cmake_minimum_required(VERSION 2.8.11)
enable_testing()

file(GLOB tests "./*.cpp")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

foreach(file ${tests} )
   get_filename_component(TEST_NAME ${file} NAME_WE)
   add_executable(${TEST_NAME} ${file})
   target_link_libraries(${TEST_NAME} networkMappingEA ${GTEST_BOTH_LIBRARIES} ${CMAKE_DL_LIBS})
   add_test(NAME ${TEST_NAME} 
	    COMMAND ${TEST_NAME} "./inputs") 
endforeach()
