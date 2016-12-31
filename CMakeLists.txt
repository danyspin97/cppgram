cmake_minimum_required(VERSION 2.8)
project(cppgram)

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

include_directories(include)

add_subdirectory(opt)
add_subdirectory(src)

set(CPPGRAM_LIBRARIES cppgram CACHE INTERNAL "")
set(CPPGRAM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
