add_library(gdl STATIC
                "${PROJECT_SOURCE_DIR}/include/gdl.h"
                bit.h file.h gdlmath.h hash.h input.h matrix.h mem.h quat.h sid.h str.h sys.h thread.h time.h uid.h vector.h win.h workq.h
                gdlmath.cpp matrix.cpp quat.cpp workq.cpp)
target_precompile_headers(gdl PUBLIC pch.h)

if (WIN32)
   target_sources(gdl PRIVATE win32_win.h
                              win32_file.cpp win32_input.cpp win32_mem.cpp win32_str.cpp win32_sys.cpp win32_thread.cpp win32_time.cpp win32_win.cpp)
endif()

if(MSVC)
    target_compile_options(gdl PUBLIC "/Zc:__cplusplus")
    target_compile_options(gdl PUBLIC "/W3")
endif()

target_compile_definitions(gdl PRIVATE
                               # Platform
                               $<$<PLATFORM_ID:Windows>:PLATFORM_WIN32>
                               # Configuration
                               $<$<CONFIG:Debug>:GDL_DEBUG>
                               $<$<CONFIG:Release>:GDL_RELEASE>)
