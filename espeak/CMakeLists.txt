cmake_minimum_required(VERSION 3.7)
project(espeak)

set(CMAKE_CXX_STANDARD 14)

add_executable(espeak main.cpp speak.cpp speak.hpp)