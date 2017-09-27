file(GLOB OBJS *.c *.h *.cpp *.hpp)

add_executable(Core-Test ${OBJS})
target_link_libraries(Core-Test Core)
