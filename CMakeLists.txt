cmake_minimum_required(VERSION 3.14)

project(SDL_learning LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Disables GNU extensions, enforcing strict standard compliance.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(FetchContent)

FetchContent_Declare(
  SDL
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        release-3.2.16
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

FetchContent_Declare(
  SDL_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG        release-3.2.4
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL)
FetchContent_MakeAvailable(SDL_image)

file(GLOB UTILS_SOURCES "${SOURCE_ROOT_DIR}/utils/source/*.cpp")

add_executable(main
    src/main.cpp
    ${UTILS_SOURCES}
)

target_include_directories(main PUBLIC
    ${SOURCE_ROOT_DIR}
    ${SOURCE_ROOT_DIR}/utils/include
)


target_link_libraries(main PRIVATE 
  SDL3::SDL3-shared
  SDL3_image::SDL3_image-shared
)

target_compile_features(main PRIVATE cxx_std_17)
