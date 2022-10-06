cmake_minimum_required(VERSION 3.20)
project(TALC)

set(CMAKE_CXX_STANDARD 17)
find_package( CURL )
find_package( cJSON )


add_executable(talc main.cpp argParser.cpp github.cpp repo.cpp commit.cpp bar.cpp time.cpp)
target_link_libraries(talc curl cjson)