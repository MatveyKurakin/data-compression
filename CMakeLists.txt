cmake_minimum_required(VERSION 3.5)

project(DataCompression)

include_directories(include gtest)

add_subdirectory(src)
add_subdirectory(gtest)
add_subdirectory(test)
add_subdirectory(huffman)
