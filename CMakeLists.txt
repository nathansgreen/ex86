cmake_minimum_required(VERSION 2.6) 
project(ex86)

add_definitions(-DREGISTER_SIZE=64 -Wall -Werror -pedantic -std=c99)

add_subdirectory(libex86)
add_subdirectory(iex86)
