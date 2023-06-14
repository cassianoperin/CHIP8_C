#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// Display
extern unsigned int display_pixel_ON_color;
extern unsigned int display_pixel_OFF_color;
extern unsigned int display_pixels[2048];
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

// Input
extern void input_keyboard();

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