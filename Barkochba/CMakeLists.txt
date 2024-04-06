cmake_minimum_required(VERSION 3.16)
project(NAME LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_executable(NAME src/main.cpp)
include_directories(include)
target_sources(NAME
    PRIVATE
        src/main.cpp
        src/qmaster.cpp
        include/node.h
        include/qmaster.h
)
target_compile_features(NAME PRIVATE cxx_std_17)

target_compile_options(NAME PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_options(NAME PRIVATE -fsanitize=address)

install(TARGETS NAME)