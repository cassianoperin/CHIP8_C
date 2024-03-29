// ---------------------------- 35 original CHIP8 opcodes ---------------------------- //
// 0NNN: Execute RCA 1802 machine language routine at address NNN
// 00E0: Clear the screen
// 00EE: Return from subroutine
// 1NNN: Jump to address NNN
// 2NNN: Call subroutine at address NNN
// 3XNN: Skip the following instruction if the value of register VX equals NN
// 4XNN: Skip the following instruction if the value of register VX is not equal to NN
// 5XY0: Skip the following instruction if the value of register VX is equal to the value of register VY
// 6XNN: Set VX to NN
// 7XNN: Add NN to VX
// 8XY0: Set VX to the value in VY
// 8XY1: Set VX to VX OR VY
// 8XY2: Set VX to VX AND VY
// 8XY3: Set VX to VX XOR VY
// 8XY4: Add the value of register VY to register VX. Set VF to 01 if a carry occurs. Set VF to 00 if a carry does not occur
// 8XY5: Subtract the value of register VY from register VX. Set VF to 00 if a borrow occurs. Set VF to 01 if a borrow does not occur
// 8XY6: Store the value of register VY shifted right one bit in register VX. Set register VF to the least significant bit prior to the shift
// 8XY7: Set register VX to the value of VY minus VX. Set VF to 00 if a borrow occurs. Set VF to 01 if a borrow does not occur
// 8XYE: Store the value of register VY shifted left one bit in register VX. Set register VF to the most significant bit prior to the shift
// 9XY0: Skip the following instruction if the value of register VX is not equal to the value of register VY
// ANNN: Store memory address NNN in register I
// BNNN: Jump to address NNN + V0
// CXNN: Set VX to a random number with a mask of NN
// DXYN: Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I. Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
// EX9E: Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed
// EXA1: Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed
// FX07: Store the current value of the delay timer in register VX
// FX0A: Wait for a keypress and store the result in register VX
// FX15: Set the delay timer to the value of register VX
// FX18: Set the sound timer to the value of register VX
// FX1E: Add the value stored in register VX to register I
// FX29: Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
// FX33: Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I+1, and I+2
// FX55: Store the values of registers V0 to VX inclusive in memory starting at address I. I is set to I + X + 1 after operation
// FX65: Fill registers V0 to VX inclusive with the values stored in memory starting at address I. I is set to I + X + 1 after operation
// -------------------------------- Undocumented opcode -------------------------------- //
// 02D8: LDA 02, I // Load from memory at address I into V[00] to V[02]
// 02E4: LDF I, V[02] // Load into I the address of the 8x5 font with index as value of V[02]

#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// Display
extern unsigned int display_pixel_ON_color;
extern unsigned int display_pixel_OFF_color;
extern unsigned int display_pixels[8192];
// Screen Size
extern unsigned char display_SCREEN_WIDTH_X;
extern unsigned char display_SCREEN_HEIGHT_Y;
// Legacy Opcodes and Quirks
extern bool quirk_Memory_legacy_Fx55_Fx65;
extern bool quirk_Shifting_legacy_8xy6_8xyE;
extern bool quirk_Spacefight2091_Fx1E;
extern bool quirk_Clipping_Dxyn;
extern bool quirk_Resize_SCHIP_00FE_00FF;
extern bool quirk_Scroll_SCHIP_00CN_00FB_00FC;
extern bool quirk_ETI660_64x32_screen;
extern bool quirk_Jump_with_offset_Bnnn;
extern bool quirk_LoRes_Wide_Sprite_Dxy0;
extern bool quirk_VF_Reset_8xy1_8xy2_8xy3;
extern bool quirk_ClockProgram_fonts;
extern bool quirk_display_wait;
// File name
extern char *filename;
// CPU
extern unsigned short	PC;
extern unsigned short	Stack[];
extern unsigned short	SP;
extern bool             cpu_debug_mode;
extern char             cpu_debug_message[120];
extern unsigned short	Opcode;
extern unsigned char	V[16];
extern unsigned short	I;
extern unsigned char	Memory[4096];
extern unsigned char    Key[16];
extern unsigned char	DelayTimer;
extern unsigned char	SoundTimer;
extern bool             cpu_draw_flag;
extern unsigned char    key_FX0A;
extern bool             key_FX0A_pressed;
// Debug Pixels
extern bool             debug_pixels;

// Input
extern void input_keyboard();

// Print the binary representation of a byte
extern void print_bin(unsigned char value);

// CPU

// -------------------------------------- Functions ------------------------------------- //
// CHIP-8
void opc_chip8_0NNN();
void opc_chip8_00E0();
void opc_chip8_00EE();
void opc_chip8_1NNN();
void opc_chip8_2NNN();
void opc_chip8_3XNN();
void opc_chip8_4XNN();
void opc_chip8_5XY0();
void opc_chip8_6XNN();
void opc_chip8_7XNN();
void opc_chip8_8XY0(unsigned char x, unsigned char y);
void opc_chip8_8XY1(unsigned char x, unsigned char y);
void opc_chip8_8XY2(unsigned char x, unsigned char y);
void opc_chip8_8XY3(unsigned char x, unsigned char y);
void opc_chip8_8XY4(unsigned char x, unsigned char y);
void opc_chip8_8XY5(unsigned char x, unsigned char y);
void opc_chip8_8XY6(unsigned char x, unsigned char y);
void opc_chip8_8XY7(unsigned char x, unsigned char y);
void opc_chip8_8XYE(unsigned char x, unsigned char y);
void opc_chip8_9XY0();
void opc_chip8_ANNN();
void opc_chip8_BNNN();
void opc_chip8_CXNN();
void opc_chip8_DXYN();
void opc_chip8_EX9E(unsigned char x);
void opc_chip8_EXA1(unsigned char x);
void opc_chip8_FX0A(unsigned char x);
void opc_chip8_FX07(unsigned char x);
void opc_chip8_FX15(unsigned char x);
void opc_chip8_FX18(unsigned char x);
void opc_chip8_FX1E(unsigned char x);
void opc_chip8_FX29(unsigned char x);
void opc_chip8_FX33(unsigned char x);
void opc_chip8_FX55(unsigned char x);
void opc_chip8_FX65(unsigned char x);
// CHIP-8 Undocumented
void opc_chip8_ND_02D8();