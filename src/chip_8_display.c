#include "chip_8_display.h"

enum Chip8Result initialize_SDL(struct SDL_Context *sdl_context) {
    int result = SUCCESS;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        result = SDL_ERROR;
        // TODO: more complex return type that can hold the SDL error
    }

    sdl_context->window = SDL_CreateWindow("Chip 8 Emulator", DISPLAY_WIDTH * 4, DISPLAY_HEIGHT * 4, 0);

    if (!sdl_context->window) {
        result = SDL_ERROR;
        // TODO: more complex return type that can hold the SDL error
    }

    return result;
}

enum Chip8Result update_display(struct Chip8Context *context) {

    return SUCCESS;
}

enum Chip8Result run_chip_8_context(struct Chip8Context *context) {
    update(context);
    return update_display(context);
}

void quit_SDL(struct SDL_Context *context) {
    SDL_DestroyWindow(context->window);
    SDL_Quit();
}
