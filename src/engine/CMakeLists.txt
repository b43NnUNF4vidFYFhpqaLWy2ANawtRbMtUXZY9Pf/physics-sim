cmake_minimum_required(VERSION 3.27.1)
project(engine)
add_library(engine STATIC
    main.cpp
    timer.cpp
    window.cpp
)