cmake_minimum_required(VERSION 3.13)
project(listen)

set(CMAKE_CXX_STANDARD 20)
find_package(CURL REQUIRED)

link_directories("/usr/local/include/curl")

add_executable(listen main_listen.cpp Speach_recognizer.hpp Speach_recognizer.cpp Dictionary_txt.cpp Dictionary_txt.hpp)
target_link_libraries(listen pocketsphinx sphinxbase sphinxad asound curl)