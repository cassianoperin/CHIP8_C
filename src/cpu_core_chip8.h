#pragma once

// --------------------------------- External Variables --------------------------------- //
// Display
extern unsigned char SCREEN_WIDTH;
extern unsigned char SCREEN_HEIGHT;
extern unsigned int  PIXEL_ON_COLOR;
extern unsigned int  PIXEL_OFF_COLOR;
extern unsigned int pixels[2048];
extern bool drawFlag;
extern bool drawFlagCounter;
// Screen Size
extern unsigned char SizeX;
extern unsigned char SizeY;
// SCHIP
extern bool SCHIP;
extern bool SCHIP_LORES;
// Legacy Opcodes and Quirks
extern bool Quirk_Memory_Legacy_Fx55_Fx65;
extern bool Quirk_Shifting_Legacy_8xy6_8xyE;
extern bool Quirk_Spacefight2091_FX1E;
extern bool Quirk_Clipping_DXYN;
extern bool Quirk_Resize_SCHIP_00FE_00FF;
extern bool Quirk_Scroll_SCHIP_00CN_00FB_00FC;
extern bool Quirk_ETI660_64x32_screen;
extern bool Quirk_Jump_with_offset_Bnnn;
extern bool Quirk_LoResWideSprite_DXY0;
extern bool Quirk_VF_Reset_8XY1_8XY2_8XY3;
extern bool Quirk_ClockProgram_Fonts;

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