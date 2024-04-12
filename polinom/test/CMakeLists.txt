cmake_minimum_required(VERSION 3.28)
project(test)

# Указание пути к заголовочным файлам gtest.h
include_directories(../gtest/gtest.h)

# Добавление исполняемого файла тестов
add_executable(TestPolinom TestPolinom.cpp test_main.cpp)

# Линковка с библиотекой GTest
target_link_libraries(TestPolinom gtest)