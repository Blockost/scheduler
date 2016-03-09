# cmake_minimum_required(VERSION <specify CMake version here>)
project(ProjetGSI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -Wall -Wextra -Weffc++ -Wno-long-long")

set(SOURCE_FILES src/main.cpp)
add_executable(ProjetGSI ${SOURCE_FILES})