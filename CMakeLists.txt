cmake_minimum_required(VERSION 3.29)
project(tp1_ordonnancement_AdamUL3)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp1_ordonnancement_AdamUL3
    Processus.cpp
        Processus.h
        simulateur.cpp
        File.h
        File.cpp
        Ordonnanceur.h
        Ordonnanceur.cpp
        ContratException.cpp)
