cmake_minimum_required(VERSION 3.16)
project(ImageProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(image_processor
    src/main.cpp
    src/Image.cpp
)

target_include_directories(image_processor PRIVATE include)

target_compile_options(image_processor PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)