cmake_minimum_required(VERSION 3.16)

project(Task1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/editor)

add_executable(prog)

target_sources(prog
    PRIVATE
        src/main.cpp
)

target_link_libraries(prog
    PRIVATE
        editor
)
