cmake_minimum_required(VERSION 3.12)

# Project name
project(Game VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively grab all .cpp files from src/
file(GLOB_RECURSE GAME_SRC CONFIGURE_DEPENDS
    src/*.cpp
)

# Create executable
add_executable(Game ${GAME_SRC})

# Include headers (if you keep headers in src/ or include/)
target_include_directories(Game PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(Game PRIVATE Engine)

# --- Post-build step: copy Engine shared library to Game binary dir ---
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Engine>         # the built DLL/SO/DYLIB
        $<TARGET_FILE_DIR:Game>       # destination = Game executable's folder
)