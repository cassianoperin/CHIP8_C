#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
extern char *lib_game_signature;

// ---------------------------------- Global Variables ---------------------------------- //
// SDL Video
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

// // SDL Font
TTF_Font *font;
SDL_Surface *text;

// Game path and ROM name
char* filename;

// Control the Main loop exit
bool quit;

// Frame Counters
unsigned int frame = 0;             // Frame counter
unsigned int frame_counter = 0;     // Frame per second

// Cycle Counters
unsigned int cycle = 0;             // Main loop cycles
unsigned int cycle_counter = 0;     // Main loop cyles/second

// CPU Counters
unsigned int cycle_cpu = 0;		    // Executed cpu cycles
unsigned int cycle_counter_cpu = 0; // CPU instructions per second

