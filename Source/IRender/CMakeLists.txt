set                         (IRENDER_TARGET_PLATFORMS "OpenGL" "DirectX")
define_list_configuration   (IRENDER_TARGET_PLATFORM "OpenGL;DirectX" "Specifies the target rendering platform.")

if("${IRENDER_TARGET_PLATFORM}" STREQUAL "OpenGL")
  find_package          (OpenGL)
  link_libraries        (${OPENGL_LIBRARIES})
  include_directories   (${OPENGL_INCLUDE_DIR})
elseif("${IRENDER_TARGET_PLATFORM}" STREQUAL "DirectX")
  ## Do Nothing
endif()

set                   (EXT *(.c|.h|.cpp|.hpp))
file                  (GLOB OBJS (${EXT}) | (${IRENDER_TARGET_PLATFORM}/${EXT}) | (${IRENDER_TARGET_PLATFORM}/win/${EXT}) | (${IRENDER_TARGET_PLATFORM}/lin/${EXT}))
add_library           (IRender SHARED ${OBJS})


if(WIN32)
target_compile_definitions        (IRender PUBLIC IRENDER_API=__declspec\(dllexport\) PUBLIC APIENTRY=__stdcall)
else()
target_compile_definitions        (IRender PUBLIC IRENDER_API=)
endif()

if("${IRENDER_TARGET_PLATFORM}" STREQUAL "OpenGL")
  target_compile_definitions      (IRender PUBLIC IRENDER_OPENGL)
elseif("${IRENDER_TARGET_PLATFORM}" STREQUAL "DirectX")
  target_compile_definitions      (IRender PUBLIC IRENDER_DIRECTX)
endif()