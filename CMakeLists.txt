cmake_minimum_required  (VERSION 2.6)

project                 (D3DE)

link_directories        (${CMAKE_BINARY_DIR}/lib)
include_directories     (${CMAKE_CURRENT_LIST_DIR}/Source)

set(CMAKE_CXX_STANDARD              14)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

add_definitions(-DOUTPUT_DIRECTORY="${CMAKE_BINARY_DIR}/bin")

function(define_configuration _DEFINE _VAL _TYPE _DESC)
  set(${_DEFINE} ${_VAL} CACHE ${_TYPE} "${_DESC}")
  add_definitions(-D${_DEFINE}="${${_DEFINE}}")
endfunction()

function(define_list_configuration _DEFINE _VALS _DESC)
  define_configuration(${_DEFINE} ${_VALS} STRING, ${_DESC})
  set_property(CACHE ${_DEFINE} PROPERTY STRINGS ${_VALS})
endfunction()

define_configuration      (LOG_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Log" PATH "Specifies the output directory for log files.")
define_configuration      (RESOURCE_DIRECTORY   "${CMAKE_CURRENT_LIST_DIR}/Resources" PATH "Specifies the directory for resource documents.")

add_subdirectory          (Source/Platform)
add_subdirectory          (Source/IRender)
add_subdirectory          (Source/Types)
add_subdirectory          (Source/Core)

add_subdirectory          (Source/Test)

add_subdirectory          (Source/Application)
