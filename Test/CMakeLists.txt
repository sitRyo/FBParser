cmake_minimum_required(version 2.8)
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(regex_test regex.cpp)
#target_link_libraries(regex_test filesystem)