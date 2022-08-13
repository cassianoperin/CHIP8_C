#pragma once

void opc_chip8_00E0();
void opc_chip8_00EE();
void opc_chip8_1NNN();
void opc_chip8_2NNN();
void opc_chip8_3XNN();
void opc_chip8_4XNN();
void opc_chip8_6XNN();
void opc_chip8_7XNN();
void opc_chip8_8XY0(unsigned short x, unsigned short y);
void opc_chip8_8XY2(unsigned short x, unsigned short y);
void opc_chip8_8XY4(unsigned short x, unsigned short y);
void opc_chip8_8XY5(unsigned short x, unsigned short y);
void opc_chip8_8XY6(unsigned short x, unsigned short y);
void opc_chip8_8XYE(unsigned short x, unsigned short y);
void opc_chip8_9XY0();
void opc_chip8_ANNN();
void opc_chip8_CXNN();
void opc_chip8_DXYN();
void opc_chip8_EXA1(unsigned short x);
void opc_chip8_FX07(unsigned short x);
void opc_chip8_FX15(unsigned short x);
void opc_chip8_FX18(unsigned short x);
void opc_chip8_FX1E(unsigned short x);
void opc_chip8_FX29(unsigned short x);
void opc_chip8_FX33(unsigned short x);
void opc_chip8_FX55(unsigned short x);
void opc_chip8_FX65(unsigned short x);