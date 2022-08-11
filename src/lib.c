#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

// ---------------------------- Tickers ---------------------------- //

// Use with actions that should be executed each second
bool ticker_second(unsigned int lastTime, unsigned int currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second
	if (currentTime > lastTime + (1000)) {
		success = true;
	}
	
	return success;
}

// Use with actions that should be executed 60 times per second
bool ticker_fps(unsigned int lastTime, unsigned int currentTime)
{

	unsigned int FPS  = 60;

	//Initialization flag
	bool success = false;


	// Check if it passed one second / FPS
	if (currentTime > lastTime + (1000/FPS)) {
	// if (currentTime > lastTime + (16)) {
		success = true;
	}

	return success;
}

// --------------------------- File load --------------------------- //

// Load rom into memory
void load_rom(char* filename, unsigned char *mem, unsigned int mem_size)
{
	int PC = 0x200;

	// ----------------- Read File ----------------- //

	FILE* rom = fopen(filename, "rb");
	if (!rom) {
		fprintf(stderr, "Unable to open file '%s'!\n", filename);
		exit(1);
	}
	fread(&mem[PC], 1, mem_size - PC, rom);
	fclose(rom);

	// Print Memory
	// for(int i = 0; i < mem_size; i++)
	// 	printf("%02X ", mem[i]);
	
	printf("\n\n");
}