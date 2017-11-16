file                (GLOB OBJS *.c *.h *.cpp *.hpp)

add_executable      (ALL_TESTS ${OBJS})

function(add_test_directory _TEST)
  add_subdirectory  (${_TEST})
  add_dependencies  (ALL_TESTS Test-${_TEST})
endfunction()

add_test_directory  (Types)
add_test_directory  (Core)