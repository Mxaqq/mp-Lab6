cmake_minimum_required(VERSION 3.28)
project(polinomlib)

add_library(polinomlib STATIC)
target_sources(polinomlib PRIVATE TMonom.h TPolinom.h TMonom.cpp TPolinom.cpp)
target_include_directories(polinomlib PUBLIC include)
