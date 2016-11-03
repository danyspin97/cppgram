cmake_minimum_required(VERSION 2.8)
project(cppgram)

include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

find_package(cpr)
if (NOT cpr_FOUND)
  add_subdirectory(opt/cpr)
endif()
add_subdirectory(src)
