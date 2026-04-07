cmake_minimum_required(VERSION 3.10)
project(huffman-algorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings and optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Poner ejecutables en build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ejecutables disponibles (uno por cada .cpp con main)
add_executable(huffman huffman.cpp)
add_executable(huffcodeco huffcodeco.cpp)
add_executable(huffmancompress huffmancompress.cpp)
add_executable(huffmandecompress huffmandecompress.cpp)
add_executable(priority_queue priority_queue.cpp)
