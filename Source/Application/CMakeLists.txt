file                    (GLOB OBJS main.cpp)
add_executable          (Application ${OBJS})
target_link_libraries   (Application Platform IRender Types Core)