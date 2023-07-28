cmake_minimum_required(VERSION 3.27.1)
project(physics)
add_library(physics STATIC
    world.cpp
    vector.cpp
    polygon.cpp
    dynamics/rigid_body.cpp
)