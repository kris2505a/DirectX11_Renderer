cmake_minimum_required(VERSION 3.20)

# ---- FIX MSVC + Ninja debug format poisoning ----
unset(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT CACHE)
unset(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT)

project("Not-Dx11" LANGUAGES CXX)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()


# ------------------------------------------------------------
# Source files (recursive)
# ------------------------------------------------------------
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.hpp"
)

add_executable (Not-Dx11
    ${PROJECT_SOURCES}
)

set_property(TARGET Not-Dx11 PROPERTY CXX_STANDARD 20)

target_include_directories(Not-Dx11 PRIVATE
    ${SRC_DIR}
)

# ------------------------------------------------------------
# SDL2 (STATIC)
# thirdparty/SDL2/include
# thirdparty/SDL2/lib/SDL2-static.lib
# ------------------------------------------------------------
set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2")

target_include_directories(Not-Dx11 PRIVATE
    ${SDL2_DIR}/include
)

target_link_directories(Not-Dx11 PRIVATE
    ${SDL2_DIR}/lib
)

target_link_libraries(Not-Dx11 PRIVATE
    SDL2-static
)

# ------------------------------------------------------------
# SDL2 main handling (NO SDL2main)
# ------------------------------------------------------------
target_compile_definitions(Not-Dx11 PRIVATE
    SDL_MAIN_HANDLED
)

# ------------------------------------------------------------
# DirectX 11 + Windows system libs
# ------------------------------------------------------------
if (WIN32)
    target_link_libraries(Not-Dx11 PRIVATE
        d3d11
        dxgi
        d3dcompiler
        user32

        # ---- required for static SDL2 ----
        winmm
        imm32
        version
        setupapi
        cfgmgr32
        ole32
        oleaut32
        uuid
    )
endif()

# ------------------------------------------------------------
# GLM (header-only)
# thirdparty/glm/glm/glm.hpp
# ------------------------------------------------------------
target_include_directories(Not-Dx11 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm
)

# TODO: Add tests and install targets if needed.
