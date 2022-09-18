#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// --------------------------------- External Variables --------------------------------- //
extern unsigned char Memory[4096];
extern char* filename;

// ---------------------------------- Global Variables ---------------------------------- //

// -------------------------------------- Functions ------------------------------------- //

// CLI
void command_line_interface(int argc, char* args[]);