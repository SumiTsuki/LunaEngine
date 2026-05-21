add_library(luna_math INTERFACE)

add_library(Luna::Math ALIAS luna_math)

target_sources(luna_math
  INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/Public/Luna_Math/Vector4.hpp"
)

target_include_directories(luna_math
  INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/Public"
)
