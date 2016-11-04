cmake_minimum_required(VERSION 2.8)
project(cppgram)

include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

find_package(CPR)
if (NOT CPR_FOUND)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/opt/cpr)
endif()
add_subdirectory(src)

set(CPPGRAM_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/lib CACHE INTERNAL "")
set(CPPGRAM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
