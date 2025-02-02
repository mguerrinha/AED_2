cmake_minimum_required(VERSION 3.27)
project(project_2_ATFMS)

set(CMAKE_CXX_STANDARD 17)

add_executable(project_2_ATFMS src/main.cpp
        src/Graph.cpp
        src/Airline.cpp
        src/Airport.cpp
        src/FlightManager.cpp
        src/Interface.cpp
        src/Interface.h
        src/Flight.cpp
        src/Flight.h
        src/Haversine.h
        src/Haversine.cpp)
