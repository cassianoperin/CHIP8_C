#pragma once

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

// Undocumented
void opc_chip8_ND_02D8();