#include <stdio.h>

#include "chip_8_display.h"

int main(int argc, char* argv[]) {
    struct Chip8Context chip8_context = init_chip8_context();

    if (argc == 2) {
        enum Chip8Runtime result = load_rom(argv[1], &chip8_context);
        if (result != SUCCESS) {
            return result;
        }
    } else if (argc == 1) {
        printf("Expected argument");
        return 1;
    } else if (argc > 1) {
        printf("Unexpected argument: %s", argv[2]);
        return 1;
    }

    struct SDL_Context sdl_context = {
        .window = NULL
    };

    if (initialize_SDL(&sdl_context) != SUCCESS) {
        quit_SDL(sdl_context);
        return 1;
    }

    run_chip_8_context(&chip8_context);

    quit_SDL(sdl_context);
    return 0;
}