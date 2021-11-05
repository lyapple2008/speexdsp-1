cmake_minimum_required(VERSION 3.6)

project(speexdsp)

add_definitions(-DHAVE_CONFIG_H -DFIXED_POINT)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fftwrap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/filterbank.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/jitter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/kiss_fft.c
    ${CMAKE_CURRENT_SOURCE_DIR}/kiss_fftr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mdf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/preprocess.c
    ${CMAKE_CURRENT_SOURCE_DIR}/resample.c
    ${CMAKE_CURRENT_SOURCE_DIR}/scal.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/smallft.c
)