find_package        (X11 REQUIRED)
link_libraries      (${X11_LIBRARIES})
include_directories (${X11_INCLUDE_DIR})

file                (GLOB OBJS *.c *.h *.cpp *.hpp)
add_library         (Platform ${OBJS})