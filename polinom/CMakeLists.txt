#CmakeList относяшийся к проекту polinom
cmake_minimum_required(VERSION 3.28)
project(polinom)

add_subdirectory(listlib)
add_subdirectory(polinomlib)
add_subdirectory(test)

add_executable(polinom main.cpp)
add_executable(TPolinom_Test TPolinom_Test.cpp)
target_link_libraries(TPolinom_Test PRIVATE polinomlib listlib)
