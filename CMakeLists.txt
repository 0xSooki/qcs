
cmake_minimum_required(VERSION 3.15)

project(QuantumCircuitSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EIGEN3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/eigen")
include_directories(${EIGEN3_INCLUDE_DIR})


set(SRC_FILES
    src/main.cpp
    src/gates/PauliX.hpp
)

# For IDEs
set(HEADER_FILES
    src/gates/PauliX.hpp
)

add_executable(QuantumCircuitSimulator ${SRC_FILES} ${HEADER_FILES})

target_include_directories(QuantumCircuitSimulator PRIVATE ${EIGEN3_INCLUDE_DIR})
