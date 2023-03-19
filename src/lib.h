#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// --------------------------------- External Variables --------------------------------- //
// Display
extern unsigned char display_FPS;
extern unsigned char Memory[4096];
// Font
extern char *string_msg1, *string_msg2, *string_msg3, *string_msg4; 
// CPU
extern unsigned int CPU_CLOCK;

// ---------------------------------- Global Variables ---------------------------------- //
char* game_signature;           // Game signature to apply quirks

// -------------------------------------- Functions ------------------------------------- //

// Ticker - Use with actions that should be executed each second = 1hz
bool ticker_second(long lastTime, long currentTime);

// Ticker - Use with actions that should be executed 60 times per second = 60hz
bool ticker_fps(long lastTime, long currentTime);

// Ticker - se with actions that should be executed 500 times per second = 500hz
bool ticker_cpu(long lastTime, long currentTime);

// Load rom into memory
void load_rom(char* filename, unsigned char *mem, unsigned int mem_size);

// Get Game Signature
char* get_game_signature(char* filename);

// Time measurement
long getMicrotime();

// Print Frames and Cycles per second on screen
void showCPS(long long unsigned int number);
void showFPS(int number);
void showCPU_CPS(int number);
