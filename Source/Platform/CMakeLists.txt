find_package        (X11 REQUIRED)
link_libraries      (${X11_LIBRARIES})
include_directories (${X11_INCLUDE_DIR})

set                 (EXT *(.c|.h|.cpp|.hpp))
file                (GLOB OBJS (${EXT})|(win/${EXT})|(lin/${EXT}))
add_library         (Platform SHARED ${OBJS})