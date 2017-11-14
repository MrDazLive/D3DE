file                (GLOB OBJS *.c *.h *.cpp *.hpp)

add_executable      (ALL_TESTS ${OBJS})

add_subdirectory    (Types)
add_subdirectory    (Core)