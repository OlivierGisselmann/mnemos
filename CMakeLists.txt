cmake_minimum_required(VERSION 3.25)

project(Mnemos)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(engine)
add_subdirectory(application)

option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()