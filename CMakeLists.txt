cmake_minimum_required  (VERSION 2.6)

project                 (D3DE)

link_directories        (${CMAKE_BINARY_DIR}/lib)
include_directories     (${CMAKE_CURRENT_LIST_DIR}/Source)

set(CMAKE_CXX_STANDARD              14)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)

set(WORKING_DIRECTORY               ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

add_subdirectory          (Source/Types)
add_subdirectory          (Source/Core)

add_subdirectory          (Source/Test/Types)
add_subdirectory          (Source/Test/Core)
