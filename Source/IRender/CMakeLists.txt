set                   (IRENDER_TARGET_PLATFORMS "OpenGL" "DirectX")
define_list_configuration  (IRENDER_TARGET_PLATFORM "OpenGL;DirectX" "Specifies the target rendering platform.")

if("${IRENDER_TARGET_PLATFORM}" STREQUAL "OpenGL")
  add_definitions(-DIRENDER_OPENGL)
endif()

find_package          (OpenGL)
link_libraries        (${OPENGL_LIBRARIES})
include_directories   (${OPENGL_INCLUDE_DIR})

set                   (EXT *(.c|.h|.cpp|.hpp))
file                  (GLOB OBJS (${EXT})|(OpenGL/${EXT})|(OpenGL/win/${EXT})|(OpenGL/lin/${EXT}))
add_library           (IRender SHARED ${OBJS})