file(GLOB OBJS *.c *.h *.cpp *.hpp)

add_executable(Test-Core ${OBJS})
target_link_libraries(Test-Core Core)
