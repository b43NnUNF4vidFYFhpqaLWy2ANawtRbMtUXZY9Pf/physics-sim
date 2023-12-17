project(demo LANGUAGES CXX)

set(DEMO_SOURCE_FILES
    window.cpp
    timer.cpp
    main.cpp
    )

set(DEMO_HEADER_FILES
    window.h
    timer.h
    )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(demo ${DEMO_SOURCE_FILES} ${DEMO_HEADER_FILES})
target_include_directories(demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(demo PUBLIC physics ${SDL2_LIBRARIES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
