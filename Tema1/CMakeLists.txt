cmake_minimum_required(VERSION 3.0)

project(app_project)

add_executable(tema3 main.cpp)

# Find and link threads library
find_package(Threads REQUIRED)
target_link_libraries(tema3 Threads::Threads)