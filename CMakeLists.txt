cmake_minimum_required(VERSION 3.14)
project(SDL_learning LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
  SDL
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        release-3.2.16
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL)

add_executable(main src/main.c)

target_link_libraries(main PRIVATE 
  SDL3::SDL3-shared
)

target_compile_features(main PRIVATE c_std_11)
