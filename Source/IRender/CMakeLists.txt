find_package        (OpenGL)
link_libraries      (${OPENGL_LIBRARIES})
include_directories (${OPENGL_INCLUDE_DIR})

set                 (EXT *(.c|.h|.cpp|.hpp))
file                (GLOB OBJS (${EXT})|(OpenGL/${EXT})|(OpenGL/win/${EXT})|(OpenGL/lin/${EXT}))
add_library         (IRender SHARED ${OBJS})