cmake_minimum_required(VERSION 3.10)
project(Deflate)

set(CMAKE_CXX_STANDARD 17)

add_executable(Deflate main.cpp Deflate/LZ77.cpp Deflate/LZ77.h Deflate/Huffman.cpp Deflate/Huffman.h Deflate/Deflate.cpp Deflate/Deflate.h CommandLineParser.h)