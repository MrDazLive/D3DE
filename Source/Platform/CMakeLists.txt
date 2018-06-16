find_package        (X11)
link_libraries      (${X11_LIBRARIES})
include_directories (${X11_INCLUDE_DIR})

set                 (EXT *(.c|.h|.cpp|.hpp))
file                (GLOB OBJS (${EXT}) | (win/${EXT}) | (lin/${EXT}))
add_library         (Platform SHARED ${OBJS})

if(WIN32)
target_compile_definitions      (Platform PUBLIC PLATFORM_API=__declspec\(dllexport\))
else()
target_compile_definitions      (Platform PUBLIC PLATFORM_API=)
endif()