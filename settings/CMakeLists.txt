cmake_minimum_required(VERSION 3.13)
project(settings)

set(CMAKE_CXX_STANDARD 20)

add_executable(settings main.cpp csvFileHandler.cpp csvFileHandler.hpp)