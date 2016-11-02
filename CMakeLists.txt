cmake_minimum_required(VERSION 2.8)
project(cppgram)

include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

add_subdirectory(src)
message("You can easily generate documentation by running \"make gendoc\"")
