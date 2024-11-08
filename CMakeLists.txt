cmake_minimum_required(VERSION 3.16)

project(gdl VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

# Sepcify output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

# Specify project source files
file(GLOB PROJECT_SOURCE CONFIGURE_DEPENDS
    "${SOURCE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/math/*.h"
    "${SOURCE_DIR}/math/*.cpp"
)

file(GLOB_RECURSE PROJECT_PCH CONFIGURE_DEPENDS
    "${SOURCE_DIR}/*pch.h"
    "${SOURCE_DIR}/*pch.cpp"
)

if (WIN32)
    file(GLOB PLATFORM_SOURCE CONFIGURE_DEPENDS
        "${SOURCE_DIR}/win32/*.h"
        "${SOURCE_DIR}/win32/*.cpp"
    )
endif()

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE} ${PLATFORM_SOURCE} ${PROJECT_PCH})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_precompile_headers(${PROJECT_NAME} PUBLIC "${PROJECT_PCH}")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    # Platform
    $<$<PLATFORM_ID:Windows>:PLATFORM_WIN32>
    # Configuration
    $<$<CONFIG:Debug>:GDL_DEBUG>
    $<$<CONFIG:Release>:GDL_RELEASE>
)
