file(GLOB OBJS *.c *.h *.cpp *.hpp)

add_executable(Test-Types ${OBJS})
target_link_libraries(Test-Types Core Types)