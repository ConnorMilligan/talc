cmake_minimum_required(VERSION 3.20)
project(TALC)

set(SRCS "srcs/main.cpp")
set(CMAKE_CXX_STANDARD 14)
set( CURL_LIBRARY ${CMAKE_SOURCE_DIR}/lib )
set( CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include )
find_package( CURL )

include_directories( ${CURL_INCLUDE_DIRS} )
link_directories( ${CURL_LIBRARIES} )

add_executable(curl_test2 ${SRCS})
target_link_libraries(curl_test2 curl)