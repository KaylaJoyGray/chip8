#include <stdbool.h>
#include <stdint.h>

enum Chip8Runtime {
    SUCCESS = 0,
    FILE_READ_ERROR = 1,
    ROM_SIZE_EXCEEDED = 1,
    SDL_ERROR = -1,
};

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define MEMORY_SIZE 4096

struct Chip8Context {
    bool ld_flag;   // is there a ROM loaded to memory?

    uint16_t PC; // Program Counter, stores the currently executing address
    // Most Chip-8 programs start at 0x200
    // ETI-600 programs start at 0x600
    // The lower locations are reserved for the interpreter

    uint8_t SP; // Stack Pointer, points to the topmost level of the stack

    // general-purpose 8-bit registers V(0-F)
    uint8_t V[16];

    uint16_t I; // special-purpose 16-bit register

    uint8_t DT; // Delay Timer register
    uint8_t ST; // Sound Timer register

    uint8_t memory[MEMORY_SIZE]; // RAM

    uint16_t stack[16]; // 16 bit stack with 16 values

    // Peripherals
    bool keyboard[16];
    int display_buffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];
};

struct Chip8Context init_chip8_context();

// Loads a ROM file into the memory of the interpreter
enum Chip8Runtime load_rom(const char *file_name, struct Chip8Context *context);

// Advances the emulator by 1 update cycle
void update(struct Chip8Context *context);

// Instruction 00E0 - Clear the screen
void clear_screen(struct Chip8Context *context);

// Instruction 6xkk - LD Vx, byte
// Set Vx = kk.
//
// The interpreter puts the value byte into register Vx
void set_v(uint8_t x, uint8_t byte, struct Chip8Context *context);

// Instruction Annn - LD I, addr
// Set I = nnn.
//
// The value of register I is set to the provided address.
void set_i(uint16_t address, struct Chip8Context *context);

// Instruction 7xkk - ADD Vx, byte
// Set Vx = Vx + kk.
//
// Adds the value byte to the value of register Vx, then stores the result in Vx.
void add_vx(uint8_t x, uint8_t byte, struct Chip8Context *context);

// Instruction Dxyn - DRW Vx, Vy, nibble
// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
//
// The interpreter reads n bytes from memory, starting at the address stored in register I. These bytes are then displayed as
// sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to
// be erased, V[0x0F] is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the
// coordinates of the display, it wraps around to the opposite side of the screen.
void draw_sprite(uint8_t x, uint8_t y, uint8_t n, struct Chip8Context *context);


