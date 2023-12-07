cmake_minimum_required(VERSION 3.25)
project(Weaver)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/libreria/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(Weaver main.cpp BancoPalabras.cpp BancoPalabras.h
        Solucionador.cpp
        Solucionador.h
        Vista.cpp
        Vista.h List.cpp List.h Graph.cpp Graph.h)

target_link_libraries(Weaver sfml-graphics sfml-window sfml-system)