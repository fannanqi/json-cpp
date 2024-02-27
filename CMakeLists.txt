cmake_minimum_required(VERSION 3.10)
project(json)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 14)
find_package(jsoncpp)
include_directories(
    /usr/local/include
)
link_directories(
    /usr/local/lib
)
add_executable(json json.cpp)
target_link_libraries(json jsoncpp)