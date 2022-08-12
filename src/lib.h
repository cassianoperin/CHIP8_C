#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// ---------------------------- Tickers ---------------------------- //

// Use with actions that should be executed each second = 1hz
bool ticker_second(unsigned int lastTime, unsigned int currentTime);

// Use with actions that should be executed 60 times per second = 60hz
bool ticker_fps(unsigned int lastTime, unsigned int currentTime);

// Use with actions that should be executed 500 times per second = 500hz
bool ticker_cpu(unsigned int lastTime, unsigned int currentTime);

// --------------------------- File load --------------------------- //

// Load rom into memory
void load_rom(char* filename, unsigned char *mem, unsigned int mem_size);