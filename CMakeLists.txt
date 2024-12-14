cmake_minimum_required(VERSION 3.28)

project(event-c)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_library(event-c STATIC ${SRC})

target_include_directories(event-c PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(event-c safe-c)
