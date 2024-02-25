cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 1.0.0)
find_package(glfw3 REQUIRED)

add_executable(Test src/main.cpp)

target_link_libraries(Test GL glfw GLEW)