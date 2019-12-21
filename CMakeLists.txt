cmake_minimum_required(VERSION 3.7)
project(HTMLParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(prog Main.cpp)
target_link_libraries(prog curl)