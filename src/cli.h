#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// CPU
extern bool cpu_pause; 
extern unsigned char Memory[4096];
extern bool cpu_debug_mode;
extern bool cpu_original_draw_mode;
// Sound
extern bool sound_enabled;
// Main
extern char *filename;

// --------------------------------- External Functions --------------------------------- //
// Lib
extern void load_rom(char *filename, unsigned char *mem, unsigned int mem_size);
extern uint8_t strContains(char* string, char* toFind);

// -------------------------------------- Functions ------------------------------------- //
// CLI
void command_line_interface(int argc, char* args[]);
void print_usage(char* args[]);              