
cmake_minimum_required(VERSION 3.15)

project(QuantumCircuitSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EIGEN3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/eigen")
include_directories(${EIGEN3_INCLUDE_DIR})

set(SRC_FILES
    src/main.cpp
)

#[[
set(SRC_FILES
    src/main.cpp
    src/file_io.cpp 
    src/QuantumCircuit.cpp
    src/Qubit.cpp
    src/Gate.cpp
    src/StateVector.cpp
    src/gates/x.cpp
)

# For IDEs
set(HEADER_FILES
    src/file_io.hpp 
    src/QuantumCircuit.h
    src/Qubit.h
    src/Gate.hpp
    src/StateVector.h
    src/gates/x.hpp
)
]]

add_executable(QuantumCircuitSimulator ${SRC_FILES} ${HEADER_FILES})

target_include_directories(QuantumCircuitSimulator PRIVATE ${EIGEN3_INCLUDE_DIR})