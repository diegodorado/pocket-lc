cmake_minimum_required(VERSION 3.0)
project(pockeLC)

find_package(ALSA)
include_directories(pockeLC
  src/libs
  ${ALSA_INCLUDE_DIRS}
)

add_executable(pockeLC
  src/main.c
  src/editor.c
  src/parser.c
  src/audio.c
  src/libs/tinyexpr.c
)

target_link_libraries(pockeLC
  m
  ${ALSA_LIBRARIES}
)

target_compile_options(pockeLC PUBLIC -Wall)
