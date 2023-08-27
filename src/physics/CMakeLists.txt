cmake_minimum_required(VERSION 3.27.1)
project(physics)
add_library(physics STATIC
    dynamics/world.cpp
    dynamics/collision_body.cpp
    dynamics/rigid_body.cpp
    math/vector.cpp
    math/polygon.cpp
    collision/detection/broadphase/collision_detector.cpp
    collision/detection/broadphase/bruteforce/bruteforce.cpp
    collision/detection/broadphase/bvh/aabb.cpp
    collision/detection/broadphase/bvh/node.cpp
    collision/detection/broadphase/bvh/bvh.cpp
    collision/detection/narrowphase/simplex.cpp
    collision/detection/narrowphase/collision.cpp
    collision/detection/narrowphase/gjk.cpp
    collision/detection/narrowphase/epa.cpp
    collision/resolution/constraints/constraint.cpp
    collision/resolution/constraints/contact_constraint.cpp
    collision/resolution/constraints/contact_solver.cpp
    collision/resolution/constraints/plane_constraint.cpp
    collision/resolution/constraints/plane_solver.cpp
)