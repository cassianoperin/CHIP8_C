#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// CPU
extern unsigned char Memory[4096];
// Main
extern char *filename;

// --------------------------------- External Functions --------------------------------- //
// Lib
extern void load_rom(char *filename, unsigned char *mem, unsigned int mem_size);

// -------------------------------------- Functions ------------------------------------- //
// CLI
void command_line_interface(int argc, char* args[]);              