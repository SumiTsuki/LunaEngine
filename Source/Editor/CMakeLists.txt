add_executable(Luna main.cpp)
target_link_libraries(Luna
  PRIVATE
  Luna::Core
  SDL3::SDL3
)
