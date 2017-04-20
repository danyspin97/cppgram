cmake_minimum_required(VERSION 3.0)
project(cppgram)

# Add compiler warnings
set(COMPILER_WARNINGS "-W -Wall -Wextra -Wno-unused-parameter -Wno-comment")

# Export command for Pvs Studio
set( CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Search std::thread
find_package(Threads REQUIRED)

# Build cpr
add_subdirectory(opt)

# Add all sources file
file(GLOB_RECURSE SOURCES src/*.cpp)

#fix for Qt Creator not showing includes
file(GLOB_RECURSE HEADERS include/*.hpp)
file(GLOB_RECURSE HEADERS include/*.h)
add_custom_target(headers SOURCES ${HEADERS})

if(NOT SOURCES)
    message(FATAL_ERROR "Cannot find sources! Aborting...")
endif(NOT SOURCES)

if(NATIVE STREQUAL "no" OR NOT NATIVE)
    set(NATIVE "")
elseif(NATIVE STREQUAL "yes")
    set(NATIVE "-march=native -mtune=native")
endif(NATIVE STREQUAL "no" OR NOT NATIVE)

if(NOT OPTIMIZATION_LEVEL OR OPTIMIZATION_LEVEL STREQUAL "no")
    set(OPTIMIZATION_LEVEL "")
else()
    set(OPTIMIZATION_LEVEL "-O${OPTIMIZATION_LEVEL}")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZATION_LEVEL} ${NATIVE} ${ARCH} ${COMPILER_WARNINGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-g ${NATIVE} ${COMPILER_WARNINGS}")
endif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(CPPGRAM_LIBRARIES cppgram CACHE INTERNAL "")
set(CPPGRAM_INCLUDE_DIRS include CACHE INTERNAL "")

add_library(cppgram STATIC ${SOURCES})
target_include_directories(cppgram
    PUBLIC ${CPR_INCLUDE_DIRS}
    PUBLIC ${CPPGRAM_INCLUDE_DIRS})
target_link_libraries(cppgram ${CPR_LIBRARIES})

install(TARGETS cppgram
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library)

add_dependencies(cppgram cpr)

include(PVS-Studio.cmake)
pvs_studio_add_target(TARGET analyze ALL
    OUTPUT FORMAT errorfile
    PREPROCESSOR gcc
    LOG "${CMAKE_BINARY_DIR}/report.tasks"
    ANALYZE cppgram
    CXX_FLAGS ${PREPROCESSOR_ADDITIONAL_FLAGS}
    C_FLAGS ${PREPROCESSOR_ADDITIONAL_FLAGS}
    CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/PVS-Studio.cfg")


