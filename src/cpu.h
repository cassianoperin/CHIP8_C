#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// --------------------------------- External Variables --------------------------------- //
// Cycles
extern unsigned int  cycle;
extern unsigned int  cycle_cpu;
extern unsigned char display_FPS;
extern unsigned int  display_pixels[2048];

// ---------------------------------- Global Variables ---------------------------------- //
unsigned char	Memory[4096];		       // Memory
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
bool            cpu_original_draw_mode;     // True  = Refresh screen (draw) every time DrawFlag is set // False = Refresh screen at 60Hz
bool            cpu_draw_counter;		    // Draw Flags counter
bool            cpu_halt;                   // Halt cpu waiting for vertical blank to draw (and limit to 60 draws per second - display wait quirk)
// Debug
bool            cpu_debug_mode;  	        // Enable debug messages
char            cpu_debug_message[120];     // Debug messages
// SCHIP Specific Variables
bool            cpu_SCHIP_mode;             
bool            cpu_SCHIP_LORES_mode;       //  Lo-res mode, 64 x 32 resolution
bool            cpu_SCHIP_timer_hack;       // Enable or disable SCHIP DelayTimer Hack
unsigned char   cpu_HP48_RPL_user_flags[8]; // HP-48 RPL user flags
// Interface
bool            cpu_pause;                  // Pause emulation


// -------------------------------------- Functions ------------------------------------- //
void cpu_initialize();
void cpu_load_fonts();
void cpu_debug_print();
void cpu_interpreter();
void cpu_reset();
