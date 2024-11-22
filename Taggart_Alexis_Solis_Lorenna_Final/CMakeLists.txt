//Followed a tutorial for Cmake
cmake_minimum_required(VERSION 3.29)
project(final_again)

set(CMAKE_CXX_STANDARD 14)

add_executable(final_again main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include/SFML)
target_link_libraries(final_again sfml-system sfml-window sfml-graphics sfml-audio)
