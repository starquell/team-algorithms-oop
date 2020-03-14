cmake_minimum_required(VERSION 3.12)
project(team_algorithms_oop)

set(CMAKE_CXX_STANDARD 17)

set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${SRC_DIR})

set(SRC_LIST
        main.cpp)

option(ENABLE_TESTS "Build test for project" ON)
#if(ENABLE_TESTS)
    add_subdirectory(${TESTS_DIR})
#endif()

add_executable(${PROJECT_NAME} ${SRC_LIST})