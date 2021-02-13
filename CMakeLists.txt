cmake_minimum_required(VERSION 3.17)
project(itoi)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(itoi main.cpp)

target_link_libraries(itoi Qt5::Widgets)