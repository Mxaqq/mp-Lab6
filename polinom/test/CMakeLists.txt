cmake_minimum_required(VERSION 3.28)
project(test)

add_executable(test)
target_sources(test PRIVATE TestPolinom.cpp test_main.cpp)
target_link_libraries(test PRIVATE polinomlib listlib)
