cmake_minimum_required(VERSION 3.27.1)

project(
    physics-sim
    VERSION 1.0.0
    DESCRIPTION "Physics simulator"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/physics)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/window.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(physics PUBLIC include)
target_link_directories(${PROJECT_NAME} PRIVATE physics)

target_link_libraries(${PROJECT_NAME} PUBLIC
    physics
    ${SDL2_LIBRARIES}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)