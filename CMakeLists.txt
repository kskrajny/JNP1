cmake_minimum_required(VERSION 3.13)
project(JNP1)

set(CMAKE_CXX_STANDARD 14)

add_executable(JNP1
        main.cpp parser.h parser.cpp operations.h operations.cpp)
