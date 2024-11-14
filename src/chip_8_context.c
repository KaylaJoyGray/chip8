#include "chip_8_context.h"
#include <stdio.h>

struct Chip8Context init_chip8_context() {
    const struct Chip8Context context = {
        .ld_flag = false,
        .PC = 0x200,
        .SP = 0,
        .memory = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0 sprite
            0x20, 0x60, 0x20, 0x20, 0x70, // 1 sprite
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2 sprite
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3 sprite
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4 sprite
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5 sprite
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6 sprite
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7 sprite
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8 sprite
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9 sprite
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A sprite
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B sprite
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C sprite
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D sprite
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E sprite
            0xF0, 0x80, 0xF0, 0x80, 0x80 //  F sprite
        },
    };

    return context;
}

enum Chip8Result load_rom(const char *file_name, struct Chip8Context *context) {
    FILE *file_ptr = fopen(file_name, "rb");

    if (file_ptr == NULL) {
        return FILE_READ_ERROR;
    }

    char c = ' ';
    for (int n = 0; n < MEMORY_SIZE && c != EOF; ++n) {
        c = getc(file_ptr);
        context->memory[context->PC + n] = c;
    }

    fclose(file_ptr);

    if (c != EOF) {
        return ROM_SIZE_EXCEEDED;
    }
    return SUCCESS;
}

void update(struct Chip8Context *context) {
}

void clear_screen(struct Chip8Context *context) {
    for (int r = 0; r < DISPLAY_WIDTH; ++r) {
        for (int c = 0; c < DISPLAY_HEIGHT; ++c) {
            context->display_buffer[r][c] = 0;
        }
    }
}

void set_v(const uint8_t x, const uint8_t byte, struct Chip8Context *context) {
    context->V[x] = byte;
}

void set_i(const uint16_t address, struct Chip8Context *context) {
    context->I = address;
}

void add_vx(const uint8_t x, const uint8_t byte, struct Chip8Context *context) {
    context->V[x] += byte;
}

void draw_sprite(const uint8_t x, const uint8_t y, const uint8_t n, struct Chip8Context *context) {
    context->V[0x0F] = 0;

    for (int row = 0; row < n; ++row) {
        for (int b = 0; b < 8; ++b) {
            uint16_t nx = x + b;
            uint16_t ny = y + row;

            if (nx > DISPLAY_WIDTH)
                nx = 0 + (nx - DISPLAY_WIDTH);

            if (ny > DISPLAY_HEIGHT)
                ny = 0 + (ny - DISPLAY_HEIGHT);

            const int sprite_bit = context->memory[context->I + row] >> 8 - b;
            const int display_bit = context->display_buffer[x][y];

            if (sprite_bit && display_bit) {
                context->V[0x0F] = 1;
            }

            context->display_buffer[nx][ny] = display_bit & sprite_bit;
        }
    }
}
