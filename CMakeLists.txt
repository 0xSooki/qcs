cmake_minimum_required(VERSION 3.15)
project(QuantumCircuitSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(EIGEN3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/eigen")
include_directories(${EIGEN3_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SRC_FILES
    src/main.cpp
)

# For IDEs
set(HEADER_FILES
)

add_executable(QuantumCircuitSimulator ${SRC_FILES} ${HEADER_FILES})
target_include_directories(QuantumCircuitSimulator PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(QuantumCircuitSimulator PRIVATE sfml-graphics)
target_compile_features(QuantumCircuitSimulator PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET QuantumCircuitSimulator
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
