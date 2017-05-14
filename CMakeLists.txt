cmake_minimum_required(VERSION 3.0)
project(cppgram)

# Export command for Pvs Studio
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

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


