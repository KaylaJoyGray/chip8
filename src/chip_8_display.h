#include "SDL3/SDL.h"

#include "chip_8_context.h"

struct SDL_Context {
    SDL_Window* window;
};

enum Chip8Result initialize_SDL(struct SDL_Context *sdl_context);

enum Chip8Result run_chip_8_context(struct Chip8Context *context);

void quit_SDL();

