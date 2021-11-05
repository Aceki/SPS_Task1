cmake_minimum_required(VERSION 3.16)

project(Editor LANGUAGES CXX)

add_library(editor)

target_include_directories(editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(editor 
    PRIVATE
        src/editor_buffer.cpp
)
