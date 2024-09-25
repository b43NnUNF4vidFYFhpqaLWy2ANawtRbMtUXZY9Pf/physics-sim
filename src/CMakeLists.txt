set(PHYSICS_SOURCE_FILES
    world.cpp
    dynamics/collision_body.cpp
    dynamics/rigid_body.cpp
    math/vector.cpp
    math/polygon.cpp
    collision/collision.cpp
    collision/observer/collision_notifier.cpp
    collision/detection/broadphase/bruteforce/bruteforce.cpp
    collision/detection/broadphase/bvh/aabb.cpp
    collision/detection/broadphase/bvh/node.cpp
    collision/detection/broadphase/bvh/bvh.cpp
    collision/detection/narrowphase/simplex.cpp
    collision/detection/narrowphase/gjk.cpp
    collision/detection/narrowphase/epa.cpp
    collision/resolution/constraints/constraint.cpp
    collision/resolution/constraints/contact_constraint.cpp
    collision/resolution/constraints/contact_solver.cpp
    collision/resolution/constraints/plane_constraint.cpp
    collision/resolution/constraints/plane_solver.cpp)

set(PHYSICS_HEADER_FILES
    ../include/world.h
    ../include/collision_body.h
    ../include/rigid_body.h
    ../include/vector.h
    ../include/polygon.h
    ../include/collision.h
    ../include/collision_observer.h
    ../include/collision_notifier.h
    ../include/collision_detector.h
    ../include/bruteforce.h
    ../include/aabb.h
    ../include/node.h
    ../include/bvh.h
    ../include/simplex.h
    ../include/gjk.h
    ../include/epa.h
    ../include/constraint.h
    ../include/contact_constraint.h
    ../include/contact_solver.h
    ../include/plane_constraint.h
    ../include/plane_solver.h
    )

add_library(physics STATIC ${PHYSICS_SOURCE_FILES} ${PHYSICS_HEADER_FILES})
target_include_directories(physics PUBLIC ../include)
