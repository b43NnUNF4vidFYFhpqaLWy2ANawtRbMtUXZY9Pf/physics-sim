cmake_minimum_required(VERSION 3.27.1)
project(physics)
add_library(physics STATIC
    dynamics/world.cpp
    dynamics/collision_body.cpp
    dynamics/rigid_body.cpp
    math/vector.cpp
    math/polygon.cpp
    collision/detection/simplex.cpp
    collision/detection/collision.cpp
    collision/detection/gjk.cpp
    collision/detection/epa.cpp
    collision/resolution/constraints/constraint.cpp
    collision/resolution/constraints/contact_constraint.cpp
    collision/resolution/constraints/contact_solver.cpp
    collision/resolution/constraints/plane_constraint.cpp
    collision/resolution/constraints/plane_solver.cpp
)