####################################################
# Cmake settings
####################################################
cmake_minimum_required (VERSION 3.9.1)

#output all the toys here
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

####################################################
# Compiler options
####################################################

#TODO: something other than gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Werror -Wpedantic -Wextra)
else()
    message(FATAL_ERROR "Compiler not supported")
endif()

####################################################
# Directory locations
####################################################
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)

####################################################
# Include them
####################################################
include_directories(${SOURCE_DIR})
include_directories(${TESTS_DIR})

####################################################
# Common source files
####################################################
set(MAIN_SRC_FILES ${SOURCE_DIR}/main.cpp)
set(TEST_SRC_FILES ${TESTS_DIR}/mainTest.cpp)
set(COMMON_SRC_FILES ${SOURCE_DIR}/minesweeper.cpp)

####################################################
# Targets
####################################################
add_executable(minesweeper ${MAIN_SRC_FILES};${COMMON_SRC_FILES})
add_executable(unittest ${TEST_SRC_FILES};${COMMON_SRC_FILES})

####################################################
# Link libraries
####################################################
find_package(GTest REQUIRED)
target_link_libraries(unittest ${GTEST_LIBRARIES})
