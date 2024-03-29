#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// Counters
// extern unsigned int  cycle;
extern unsigned char display_FPS;
extern unsigned int last_cycle_counter;
// Screen Size
extern unsigned char display_SCREEN_WIDTH_X;
extern unsigned char display_SCREEN_HEIGHT_Y;
extern unsigned int  display_pixels[8192];
extern unsigned int  display_pixel_ON_color;
extern unsigned int  display_pixel_OFF_color;
// Font
extern const char Chip8Fontset[80];
extern const char SCHIPFontset[160];
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
// Main
extern char *game_signature;
extern char *filename;
// Sound
extern bool sound_enabled;

// --------------------------------- External Functions --------------------------------- //
// Lib
extern void handle_quirks(char *game_signature);
extern void load_rom(char *filename, unsigned char *mem, unsigned int mem_size);
// CHIP-8
void opc_chip8_0NNN();
extern void opc_chip8_00E0();
extern void opc_chip8_00EE();
extern void opc_chip8_1NNN();
extern void opc_chip8_2NNN();
extern void opc_chip8_3XNN();
extern void opc_chip8_4XNN();
extern void opc_chip8_5XY0();
extern void opc_chip8_6XNN();
extern void opc_chip8_7XNN();
extern void opc_chip8_8XY0(unsigned char x, unsigned char y);
extern void opc_chip8_8XY1(unsigned char x, unsigned char y);
extern void opc_chip8_8XY2(unsigned char x, unsigned char y);
extern void opc_chip8_8XY3(unsigned char x, unsigned char y);
extern void opc_chip8_8XY4(unsigned char x, unsigned char y);
extern void opc_chip8_8XY5(unsigned char x, unsigned char y);
extern void opc_chip8_8XY6(unsigned char x, unsigned char y);
extern void opc_chip8_8XY7(unsigned char x, unsigned char y);
extern void opc_chip8_8XYE(unsigned char x, unsigned char y);
extern void opc_chip8_9XY0();
extern void opc_chip8_ANNN();
extern void opc_chip8_BNNN();
extern void opc_chip8_CXNN();
extern void opc_chip8_DXYN();
extern void opc_chip8_EX9E(unsigned char x);
extern void opc_chip8_EXA1(unsigned char x);
extern void opc_chip8_FX0A(unsigned char x);
extern void opc_chip8_FX07(unsigned char x);
extern void opc_chip8_FX15(unsigned char x);
extern void opc_chip8_FX18(unsigned char x);
extern void opc_chip8_FX1E(unsigned char x);
extern void opc_chip8_FX29(unsigned char x);
extern void opc_chip8_FX33(unsigned char x);
extern void opc_chip8_FX55(unsigned char x);
extern void opc_chip8_FX65(unsigned char x);
// CHIP-8 Undocumented
extern void opc_chip8_ND_02D8();
// SCHIP
extern void opc_schip_00FF();
extern void opc_schip_DXY0();

// ---------------------------------- Global Constants ---------------------------------- //
const int CHIP8_DEFAULT_CLOCK = 500;

// ---------------------------------- Global Variables ---------------------------------- //
unsigned char	Memory[4096];		        // Memory
unsigned short	PC;          	            // Program Counter
unsigned short	Opcode;                 	// CPU Operation Code
unsigned short	Stack[16];              	// Stack
unsigned short	SP;                     	// Stack Pointer
unsigned char	V[16];                    	// V Register
unsigned short	I;                   	    // I Register
unsigned char	DelayTimer;			        // Delay Timer
unsigned char	SoundTimer;			        // Sound Timer
unsigned char   Key[16];                    // Control the Keys Pressed
// Draw
bool            cpu_draw_flag;			    // Send the draw to screen signal
// Debug
bool            cpu_debug_mode;  	        // Enable debug messages
char            cpu_debug_message[120];     // Debug messages
// SCHIP Specific Variables
bool            cpu_SCHIP_mode;             // SCHIP mode (ENABLED or DISABLED)
bool            cpu_SCHIP_LORES_mode;       // SCHIP in Low Resolution mode (00FE)
bool            cpu_SCHIP_timer_hack;       // Enable or disable SCHIP DelayTimer Hack
unsigned char   cpu_HP48_RPL_user_flags[8]; // HP-48 RPL user flags
// Interface
bool            cpu_pause;                  // Pause emulation
// CPU Counters
unsigned int    cycle_cpu = 0;		        // Executed cpu cycles
unsigned int    cycle_counter_cpu = 0;      // CPU instructions per second
// CPU Clock
unsigned int    CPU_CLOCK  = 0;             // CPU clock speed
// Input
unsigned char   key_FX0A = 0;                // Keep track of the first key pressed, to wait it to be released as necessary on FX0A
bool            key_FX0A_pressed = false;    // keep track of the state of first key pressed to check when is released to update V[x]


// -------------------------------------- Functions ------------------------------------- //
void cpu_initialize();
void cpu_load_fonts();
void cpu_debug_print();
void cpu_interpreter();
void cpu_reset();
