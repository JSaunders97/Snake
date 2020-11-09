cmake_minimum_required(VERSION 3.10)

# set the project name
project(Snake)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SOURCES "*.cpp")

# add the executable
add_executable(Snake ${SOURCES})