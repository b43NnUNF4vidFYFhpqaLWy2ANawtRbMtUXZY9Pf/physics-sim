cmake_minimum_required(VERSION 3.27.1)
project(physics)
add_library(physics STATIC
    dynamics/world.cpp
    dynamics/collision_body.cpp
    dynamics/rigid_body.cpp
    math/vector.cpp
    math/polygon.cpp
)