project(demo LANGUAGES CXX)

set(DEMO_SOURCE_FILES
    window.cpp
    timer.cpp
    main.cpp
    collision_logger.cpp
    demos/slope_demo_world.cpp
    )

set(DEMO_HEADER_FILES
    window.h
    timer.h
    collision_logger.h
    demos/demo_world.h
    demos/slope_demo_world.h
    )

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG release-2.28.5
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
FetchContent_MakeAvailable(SDL2)

add_executable(demo ${DEMO_SOURCE_FILES} ${DEMO_HEADER_FILES})
target_include_directories(demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(demo PUBLIC physics SDL2::SDL2)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
