cmake_minimum_required(VERSION 3.20)
project(TALC)

set(CMAKE_CXX_STANDARD 14)
find_package (Curl REQUIRED)

add_executable(main main.cpp)