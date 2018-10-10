cmake_minimum_required(VERSION 2.8)

project(gpib_com)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(gpib_com gpib)


