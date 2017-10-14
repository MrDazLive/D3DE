file(GLOB OBJS *.c *.h *.cpp *.hpp)

add_library(Core ${OBJS})
target_link_libraries(Core Types)