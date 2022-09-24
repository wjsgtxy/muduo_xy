# cmake_minimum_required(VERSION <specify CMake version here>)
project(muduo_xy)

set(CMAKE_CXX_STANDARD 14)

include_directories(muduo/base)

add_executable(muduo_xy
        muduo/base/copyable.h
        muduo/base/Timestamp.cc
        muduo/base/Timestamp.h)
