cmake_minimum_required(VERSION 3.20)
project(ds)

set(CMAKE_CXX_STANDARD 14)

add_executable(ds main.cpp LinearList.cpp LinearList.h MyStack.cpp MyStack.h MyQueue.cpp MyQueue.h ListSTL.cpp ListSTL.h)
