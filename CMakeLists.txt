cmake_minimum_required(VERSION 3.25)
project(Weaver)

set(CMAKE_CXX_STANDARD 20)

add_executable(Weaver main.cpp BancoPalabras.cpp BancoPalabras.h
        Solucionador.cpp
        Solucionador.h)
