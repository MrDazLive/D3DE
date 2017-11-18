function(add_test_project _TEST)
  file                    (GLOB OBJS ${_TEST}/*(.c|.h|.cpp|.hpp))
  add_executable          (Test-${_TEST} ${OBJS})
  target_link_libraries   (Test-${_TEST} ${_TEST} Core)
  add_dependencies        (ALL_TESTS Test-${_TEST})
endfunction()

file              (GLOB OBJS main.cpp)
add_executable    (ALL_TESTS ${OBJS})

add_test_project  (Types)
add_test_project  (Core)