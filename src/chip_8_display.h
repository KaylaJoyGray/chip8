#include "SDL3/SDL.h"

#include "chip_8_context.h"

struct SDLContext {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

struct SDLContext *initialize_SDL();

enum Chip8Result run_chip_8_context(struct Chip8Context *chip_8_context, struct SDLContext *sdl_context);

void quit_SDL(struct SDLContext *context);

