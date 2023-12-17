cmake_minimum_required(VERSION 3.27.1)

project(
    physics
    VERSION 0.1.0
    DESCRIPTION "Physics simulator"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

option(BUILD_DEMO "Build the demo program")

if (BUILD_DEMO)
    add_subdirectory(demo)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
