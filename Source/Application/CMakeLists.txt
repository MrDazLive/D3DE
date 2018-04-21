find_package        (OpenGL)
link_libraries      (${OPENGL_LIBRARIES})
include_directories (${OPENGL_INCLUDE_DIR})

if (WIN32)
file                    (GLOB OBJS main.cpp glad.c)
endif (WIN32)
if (UNIX)
file                    (GLOB OBJS main.cpp)
endif (UNIX)

add_executable          (Application ${OBJS})
target_link_libraries   (Application Platform IRender Types Core)