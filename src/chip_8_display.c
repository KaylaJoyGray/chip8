#include "chip_8_display.h"

#include <stdlib.h>

struct SDLContext *initialize_SDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        // TODO: more complex return type that can hold the SDL error
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow("Chip 8 Emulator", DISPLAY_WIDTH * 4, DISPLAY_HEIGHT * 4, 0);

    if (!window) {
        // TODO: more complex return type that can hold the SDL error
        SDL_Quit();
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer) {
        // TODO: more complex return type that can hold the SDL error
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    struct SDLContext context = {
        .window = window,
        .renderer = renderer,
    };

    struct SDLContext* context_ptr = malloc(sizeof(context));

    if (!context_ptr) {
        // TODO: more complex return type that can hold the SDL error
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    *context_ptr = context;
    return context_ptr;
}

enum Chip8Result update_display(struct Chip8Context *chip_8_context, struct SDLContext *sdl_context) {
    int count = 0;
    for (int r = 0; r < DISPLAY_HEIGHT; ++r) {
        for (int c = 0; c < DISPLAY_WIDTH; ++c) {
            if (chip_8_context->display_buffer[r][c]) {
                ++count;
            }
        }
    }

    SDL_FRect rects[count];

    int at = 0;
    for (int r = 0; r < DISPLAY_HEIGHT; ++r) {
        for (int c = 0; c < DISPLAY_WIDTH; ++c) {
            if (chip_8_context->display_buffer[r][c]) {
                const SDL_FRect rect = {
                    .x = c,
                    .y = r,
                    .w = 4.0,
                    .h = 4.0,
                };
                rects[at++] = rect;
            }
        }
    }

    const SDL_FRect* rects_ptr = rects;

    if (!SDL_RenderRects(sdl_context->renderer, rects_ptr, count)) {
        return SDL_ERROR;
    }

    return SUCCESS;
}

enum Chip8Result run_chip_8_context(struct Chip8Context *chip_8_context, struct SDLContext *sdl_context) {
    update_chip_8(chip_8_context);
    return update_display(chip_8_context, sdl_context);
}

void quit_SDL(struct SDLContext *context) {
    SDL_DestroyRenderer(context->renderer);
    SDL_DestroyWindow(context->window);
    SDL_Quit();
}
