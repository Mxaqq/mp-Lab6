cmake_minimum_required(VERSION 3.28)
project(gtest)

add_library(gtest STATIC)
target_sources(gtest PRIVATE gtest-all.cc gtest.h)
target_include_directories(gtest PUBLIC include)