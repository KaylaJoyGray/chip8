cmake_minimum_required(VERSION 3.29)
project(chip8 C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

add_executable(chip8 src/main.c
        src/chip_8_context.c
        src/chip_8_display.h
        src/chip_8_display.c
        src/chip_8_context.h
        src/chip_8.h)

target_link_libraries(chip8 ${SDL3_LIBRARIES})
target_include_directories(chip8 PUBLIC ${SDL3_INCLUDE_DIRS})
target_compile_options(chip8 PUBLIC ${SDL3_CFLAGS_OTHER})
