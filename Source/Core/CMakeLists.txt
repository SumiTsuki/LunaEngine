add_library(luna_core INTERFACE)

add_library(Luna::Core ALIAS luna_core)

target_sources(luna_core
  INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/Public/Core/Core.hpp"
)

target_include_directories(luna_core
  INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/Public"
)

add_subdirectory(Luna_Math)

target_link_libraries(luna_core
  INTERFACE
  Luna::Math
)
