find_package        (OpenGL)
link_libraries      (${OPENGL_LIBRARIES})
include_directories (${OPENGL_INCLUDE_DIR})

file                    (GLOB OBJS main.cpp)
add_executable          (Application ${OBJS})
target_link_libraries   (Application Platform IRender Types Core)