cmake_minimum_required(VERSION 3.16)
project(CSGOHacks)

set(CMAKE_CXX_STANDARD 20)

add_executable(CSGOHacks src/main.cpp include/csgo.hpp include/Memory.hpp src/Memory.cpp include/wallhack.hpp src/wallhack.cpp)