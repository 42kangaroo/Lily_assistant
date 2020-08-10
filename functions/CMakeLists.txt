cmake_minimum_required(VERSION 3.13)
project(functions)

set(CMAKE_CXX_STANDARD 20)
find_package(CURL REQUIRED)

add_executable(functions main.cpp LilyStdFuncs.hpp LilyStdFuncs.cpp LilyStdFuncsString.cpp LilyStdFuncsString.hpp)
target_link_libraries(functions PUBLIC ${CURL_LIBRARIES} jsoncpp asound)