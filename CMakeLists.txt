cmake_minimum_required(VERSION 3.5)
project(pockeLC)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

message("${CMAKE_SOURCE_PATH}")


include(ExternalProject)

ExternalProject_Add(
  libsoundio
  GIT_REPOSITORY "https://github.com/andrewrk/libsoundio.git"
  INSTALL_COMMAND ""
  CMAKE_ARGS -DBUILD_EXAMPLE_PROGRAMS=OFF -DBUILD_TESTS=OFF -DENABLE_COREAUDIO=OFF -DENABLE_WASAPI=OFF -DBUILD_DYNAMIC_LIBS=OFF
)

ExternalProject_Get_Property(libsoundio install_dir)

include_directories(pockeLC
src/libs
)


find_package(JACK)
include_directories(${JACK_INCLUDE_DIR})
find_package(PulseAudio)
include_directories(${PULSEAUDIO_INCLUDE_DIR})
find_package(ALSA)
include_directories(${ALSA_INCLUDE_DIRS})
find_package(Threads)

add_executable(pockeLC
  src/main.c
  src/libs/tinyexpr.c
)
add_dependencies(pockeLC libsoundio)


message(${JACK_LIBRARY} ${PULSEAUDIO_LIBRARY} ${ALSA_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

target_link_libraries(pockeLC
  m
  pthread
  jack
  ${install_dir}/src/libsoundio-build/libsoundio.a
  ${JACK_LIBRARY}
  ${PULSEAUDIO_LIBRARY}
  ${ALSA_LIBRARIES}
)


target_compile_options(pockeLC PUBLIC -Wall)
