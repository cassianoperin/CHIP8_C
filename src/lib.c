#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "cpu.h"

// --------------------------------- External Variables --------------------------------- //
extern unsigned char FPS;

// ---------------------------------- Global Variables ---------------------------------- //
char *game_signature;		// Game signature


// ---------------------------- Tickers ---------------------------- //

// Use with actions that should be executed each second = 1hz
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

// Use with actions that should be executed 60 times per second = 60hz
bool ticker_fps(unsigned int lastTime, unsigned int currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second / FPS
	if (currentTime > lastTime + (1000/FPS)) {
	// if (currentTime > lastTime + (16)) {
		success = true;
	}

	return success;
}

// Use with actions that should be executed 500 times per second = 500hz
bool ticker_cpu(unsigned int lastTime, unsigned int currentTime)
{

	unsigned int CPU_CLOCK  = 1000;

	//Initialization flag
	bool success = false;


	// Check if it passed one second / FPS
	if (currentTime >= lastTime + (1000/CPU_CLOCK)) {
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

// ------------------------ Game Signature ------------------------- //

void get_game_signature(char* filename, char **s) {

	// Get the first 12 elements of memory
	char signature[30] = "";
	sprintf(signature, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", Memory[0x200], Memory[0x201], Memory[0x202],\
		 Memory[0x203], Memory[0x204], Memory[0x205], Memory[0x206], Memory[0x207], Memory[0x208], Memory[0x209]);

	// Sum all memory bytes
	unsigned int sum = 0;
	char sum_string[10] = "";
	for ( int i = 0x200 ; i < sizeof(Memory) ; i++ ) {
		sum += Memory[i];
	}
	sprintf(sum_string, "%d", sum);

	// Unify the 12 first bytes and the sum into the final signature
	sprintf(signature + strlen(signature), "+%s", sum_string);

	// Update the game_signature pointer
	*s = signature;
}