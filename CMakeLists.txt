cmake_minimum_required(VERSION 3.20)
project(TALC)

set(CMAKE_CXX_STANDARD 14)
set( CURL_LIBRARY ${CMAKE_SOURCE_DIR}/curl/lib )
set( CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/curl/include )
find_package( CURL )

include_directories( ${CURL_INCLUDE_DIRS} )
link_directories( ${CURL_LIBRARIES} )

add_executable(talc main.cpp talcutil.cpp)
target_link_libraries(talc curl)