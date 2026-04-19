cmake_minimum_required(VERSION 3.28)

project(event-c)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

if(DEFINED ENV{ZEPHYR_BASE})
    target_sources(app PRIVATE ${SRC})
    target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
else()
    add_library(event-c STATIC)
    target_sources(safe-c PRIVATE ${SRC})
    target_include_directories(event-c PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
    target_link_libraries(event-c safe-c)
endif()
