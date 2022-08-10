#include <stdio.h>
#include <string.h>
#include "cpu.h"

// Global Variables
unsigned char	Memory[4096];		// Memory
unsigned short	PC;          	  	// Program Counter
unsigned short	Opcode;           	// CPU Operation Code
unsigned short	Stack[16];        	// Stack
unsigned short	SP;               	// Stack Pointer
unsigned char	V[16];             	// V Register
unsigned short	I;                	// I Register

extern unsigned int Cycle;

void Initialize(){
	// Components
	memset(Memory, 0x00, sizeof(Memory));	// Clean Memory
	PC = 0x200;								// Start at 0x200 (default CHIP-8)
	Opcode = 0x00;
	memset(Stack, 0x00, sizeof(Stack));		// Clean Stack
	SP = 0x00;
	memset(V, 0x00, sizeof(V));				// Clean V Register
	I = 0x00;
}

void Show(){ // Missing Delay Timers and Keys
	printf("Cycle: %d\tOpcode: %04X(%04X)\tPC: %d(0x%X)\tSP: %d\tStack: [ %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ]\
	\tV: [ %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ]\tI: %d\n", Cycle, Opcode, Opcode & 0xF000, PC, PC,  SP, Stack[0],
	 Stack[1], Stack[2], Stack[3], Stack[4], Stack[5], Stack[6], Stack[7], Stack[8], Stack[9], Stack[10], Stack[11], Stack[12], Stack[13], Stack[14], Stack[15],
	  V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7], V[8], V[9], V[10], V[11], V[12], V[13], V[14], V[15], I);
}

// CPU Interpreter
void Interpreter() {
	Show();
}