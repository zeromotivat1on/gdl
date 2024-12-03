add_library(gdl STATIC
                "${PROJECT_SOURCE_DIR}/include/gdl.h"
                bit.h ecs.h file.h gdlmath.h hash.h hash_table.h input.h matrix.h mem.h msg.h quat.h sid.h sparse_set.h str.h sys.h thread.h time.h uid.h vector.h window.h workq.h
                ecs.cpp gdlmath.cpp hash_table.cpp matrix.cpp quat.cpp sparse_set.cpp workq.cpp)
target_precompile_headers(gdl PUBLIC pch.h)

if (WIN32)
   target_sources(gdl PRIVATE win32_window.h
                              win32_file.cpp win32_input.cpp win32_mem.cpp win32_msg.cpp win32_str.cpp win32_sys.cpp win32_thread.cpp win32_time.cpp win32_win.cpp)
endif()

if(MSVC)
    target_compile_options(gdl PUBLIC "/Zc:__cplusplus")
    target_compile_options(gdl PUBLIC "/W3")
endif()

target_compile_definitions(gdl PRIVATE
                               # Platform
                               $<$<PLATFORM_ID:Windows>:WIN32>
                               # Configuration
                               $<$<CONFIG:Debug>:BUILD_DEBUG>
                               $<$<CONFIG:Release>:BUILD_RELEASE>)

target_include_directories(gdl PUBLIC "${PROJECT_SOURCE_DIR}")
