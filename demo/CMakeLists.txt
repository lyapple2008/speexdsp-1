cmake_minimum_required(VERSION 3.6)

project(demo)

add_definitions(-DHAVE_CONFIG_H)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../libspeexdsp
)

add_executable(testecho 
    ${CMAKE_CURRENT_SOURCE_DIR}/testecho.c
    ${CMAKE_CURRENT_SOURCE_DIR}/wav_io.c
)

target_link_libraries(testecho speexdsp)