cmake_minimum_required(VERSION 3.5)

project(VisionLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include/)

file(GLOB SOURCES "src/*.cpp")

add_executable(VisionLib main.cpp ${SOURCES})
