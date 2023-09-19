cmake_minimum_required(VERSION 3.0)
project(talc)

# Set which project you would like to build
set(B_TARGET "src")

# Checks for git
find_package(Git REQUIRED)

# Initialize the submodule if not already done so
if(NOT EXISTS lib/glfw/CMakeLists.txt)
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${dir}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()

# Set compiler flags based on compiler
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") # Check if using GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # Check if using Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

# Set include directories
include_directories(lib/cJSON)
include_directories(lib/curl/include)

# Put profanity text into the binary directory
configure_file(${CMAKE_SOURCE_DIR}/res/profanity-words/data/en.txt ${CMAKE_BINARY_DIR}/data/profanity.txt COPYONLY)

# Set source files
file(GLOB_RECURSE PROJECT_HEADERS ${B_TARGET}/*.h)
file(GLOB_RECURSE PROJECT_SOURCES ${B_TARGET}/*.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS})

target_link_libraries(${PROJECT_NAME} curl cjson)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
