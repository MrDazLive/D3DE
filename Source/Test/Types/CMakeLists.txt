file(GLOB OBJS *.c *.h *.cpp *.hpp)

add_executable(Types-Test ${OBJS})
target_link_libraries(Types-Test Core Types)