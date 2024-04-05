#CmakeLists для проекта postfix
cmake_minimum_required(VERSION 3.28)
project(postfix)

add_subdirectory(postfixlib)
add_subdirectory(testPos)
add_subdirectory(stack)

add_executable(postfix main.cpp)
target_link_libraries(postfix PRIVATE postfixlib)
