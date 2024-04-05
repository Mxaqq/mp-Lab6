cmake_minimum_required(VERSION 3.28)
project(listlib)

add_library(listlib STATIC)
target_sources(listlib PRIVATE TList.h TNode.h main.cpp)
target_include_directories(listlib PUBLIC include)