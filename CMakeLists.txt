cmake_minimum_required(VERSION 2.8)
project(cppgram)

include_directories(include)

find_package(CPR)
if (NOT CPR_FOUND)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/opt/cpr)
endif()
add_subdirectory(src)

set(CPPGRAM_LIBRARIES cppgram CACHE INTERNAL "")
set(CPPGRAM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
