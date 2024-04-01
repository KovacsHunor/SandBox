cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject src/main.cpp)
include_directories(include)
target_sources(CMakeSFMLProject
    PRIVATE
        src/main.cpp
        src/particle.cpp
        src/particles.cpp
        include/particles.h
        include/field.h
        include/material.h
        include/particle.h
        include/util.h
)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

target_compile_options(CMakeSFMLProject PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_options(CMakeSFMLProject PRIVATE -fsanitize=address)

install(TARGETS CMakeSFMLProject)