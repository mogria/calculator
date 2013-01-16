cmake_minimum_required(VERSION 2.8)

project(calculator)

file(GLOB_RECURSE CALCULATOR_SOURCE_FILES "src/*.c")
# file(GLOB_RECURSE CALCULATOR_TEST_SOURCE_FILES "test/*.c")

set (CMAKE_C_FLAGS "-g -Wall")

add_subdirectory(lib)

add_executable(calculator ${CALCULATOR_SOURCE_FILES})
target_link_libraries(calculator libobj)

# FIND_PATH(CHECK_INCLUDE_DIRS check.h)
# FIND_LIBRARY(CHECK_LIBRARIES NAMES check)
# include_directories(${CHECK_INCLUDE_DIRS})

# add_executable(calculator_test ${CALCULATOR_TEST_SOURCE_FILES})
# target_link_libraries(calculator_test calculator ${CHECK_LIBRARIES})

