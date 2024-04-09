# В CMakeLists.txt для polinomlib

cmake_minimum_required(VERSION 3.28)
project(polinomlib)

# Создаем библиотеку polinomlib и добавляем файлы
add_library(polinomlib STATIC TMonom.h TPolinom.h TMonom.cpp TPolinom.cpp)

# Устанавливаем публичные пути для включения
target_include_directories(polinomlib PUBLIC include)
