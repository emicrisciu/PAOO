cmake_minimum_required(VERSION 3.0)

project(app_project)

#set(CMAKE_CXX_STANDARD 11)

add_executable(tema3 main.cpp)

# Find and link pthread
find_package(Threads REQUIRED)
target_link_libraries(tema3 Threads::Threads)