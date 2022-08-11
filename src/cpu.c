#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constant.h"
#include "cpu.h"

// Global Variables
unsigned char	Memory[4096];		// Memory
unsigned short	PC;          	  	// Program Counter
unsigned short	Opcode;           	// CPU Operation Code
unsigned short	Stack[16];        	// Stack
unsigned short	SP;               	// Stack Pointer
unsigned char	V[16];             	// V Register
unsigned short	I;                	// I Register

// Variables
bool drawFlag;
bool Debug = true;
char OpcMessage[100];

// External Variables
extern unsigned int Cycle;
// extern bool Legacy_Fx55_Fx65;

void opc_chip8_2NNN();
void opc_chip8_ANNN();
void opc_chip8_FX65(unsigned short x);


// ---------------------------- CHIP-8 2xxx instruction set ---------------------------- //

// 2nnn - CALL addr
// Call subroutine at nnn.
// The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
void opc_chip8_2NNN(){
	SP++;
	Stack[SP] = PC;
	PC = Opcode & 0x0FFF;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 2nnn: Call Subroutine at 0x%d", PC);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// ---------------------------- CHIP-8 Axxx instruction set ---------------------------- //

// Annn - LD I, addr
// Set I = nnn.
// The value of register I is set to nnn.
void opc_chip8_ANNN() {
	I = Opcode & 0x0FFF;
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Annn: Set I = 0x%04X", I);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// ---------------------------- CHIP-8 Fxxx instruction set ---------------------------- //

// Fx65 - LD Vx, [I]
// Read registers V0 through Vx from memory starting at location I.
// The interpreter reads values from memory starting at location I into registers V0 through Vx.
//// I is set to I + X + 1 after operation²
//// ² Erik Bryntse’s S-CHIP documentation incorrectly implies this instruction does not modify
//// the I register. Certain S-CHIP-compatible emulators may implement this instruction in this manner.
void opc_chip8_FX65(unsigned short x) {

	unsigned short i; //TODO x and i should be char?

	for ( i = 0; i <= x; i++ ) {
		V[i] = Memory[I+i];
	}

	PC += 2;

	// If needed, run the original Chip-8 opcode (not used in recent games)
	if ( Legacy_Fx55_Fx65 ) {
		I = I + x + 1;
	}

	if ( Debug)  {

		sprintf(OpcMessage, "CHIP-8 Fx65: Read registers V[0] through V[x(0x%02X)] from memory starting at location I(0x%04X)",x, I);
		printf("\t\t%s\n" , OpcMessage);

		for ( i = 0 ; i <= x ; i ++ ) {
			printf("\t\tV[%X]= 0x%02X\n",i, V[i]);
		}
	}
}



void Initialize(){

	unsigned char i;

	// Components
	memset(Memory, 0x00, sizeof(Memory));	// Clean Memory
	PC = 0x200;								// Start at 0x200 (default CHIP-8)
	Opcode = 0x00;
	memset(Stack, 0x00, sizeof(Stack));		// Clean Stack
	SP = 0x00;
	memset(V, 0x00, sizeof(V));				// Clean V Register
	I = 0x00;

	// Load CHIP-8 8x5 fontset (Memory address 0-79)
	for ( i = 0; i < sizeof(Chip8Fontset); i++  ){
		Memory[i] = Chip8Fontset[i];
	}

	// Load SCHIP 8x10 fontset (Memory address 80-240)
	for ( i = 0; i < sizeof(SCHIPFontset); i++ ) {
		Memory[i+80] = SCHIPFontset[i];
	}

	// Legacy Opcodes and Quirks
	Legacy_Fx55_Fx65 = false;
}

// Debug
void Show(){ // Missing Delay Timers and Keys
	printf("Cycle: %d\tOpcode: %04X(%04X)\tPC: %04d(0x%04X)\tSP: %02X\tStack: [ %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ]\
	\tV: [ %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ]\tI: %04X\n", Cycle, Opcode, Opcode & 0xF000, PC, PC,  SP, Stack[0],
	 Stack[1], Stack[2], Stack[3], Stack[4], Stack[5], Stack[6], Stack[7], Stack[8], Stack[9], Stack[10], Stack[11], Stack[12], Stack[13], Stack[14], Stack[15],
	  V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7], V[8], V[9], V[10], V[11], V[12], V[13], V[14], V[15], I);
}

// CPU Interpreter
void Interpreter() {

	// Reset Flag every cycle
	drawFlag = false;

	// Read the Opcode from PC and PC+1 bytes
	Opcode = (unsigned short)Memory[PC]<<8 | (unsigned short)Memory[PC+1];

	// Debug
	if ( Debug )
		Show();

	if ( Cycle > 5 )
		exit(2);

	// Map Opcode Family
	switch ( Opcode & 0xF000 )
  	{
		// ---------------------------- CHIP-8 0xxx instruction set ---------------------------- //
		case 0x0000: //0NNN
			printf ("0000\n");
			break;
		
		// ---------------------------- CHIP-8 1xxx instruction set ---------------------------- //
		case 0x1000: // 1nnn (CHIP-8)
			printf ("1000\n");
			break;

		// ---------------------------- CHIP-8 2xxx instruction set ---------------------------- //
		case 0x2000: // 2nnn (CHIP-8)
			// printf ("2000\n");
			opc_chip8_2NNN();
			break;

		// ---------------------------- CHIP-8 3xxx instruction set ---------------------------- //
		case 0x3000: // 3xnn (CHIP-8)
			printf ("3000\n");
			break;

		// ---------------------------- CHIP-8 4xxx instruction set ---------------------------- //
		case 0x4000: // 4xnn (CHIP-8)
			printf ("4000\n");
			break;

		// ---------------------------- CHIP-8 5xxx instruction set ---------------------------- //
		case 0x5000: // 5xy0 (CHIP-8)
			printf ("5000\n");
			break;

		// ---------------------------- CHIP-8 6xxx instruction set ---------------------------- //
		case 0x6000: // 6xnn (CHIP-8)
			printf ("6000\n");
			break;

		// ---------------------------- CHIP-8 7xxx instruction set ---------------------------- //
		case 0x7000: // 7xnn (CHIP-8)
			printf ("7000\n");
			break;

		// ---------------------------- CHIP-8 8xxx instruction set ---------------------------- //
		case 0x8000: // 0x8000 instruction set
			printf ("8000\n");
			break;

		// ---------------------------- CHIP-8 9xxx instruction set ---------------------------- //
		case 0x9000: // 9xy0 (CHIP-8)
			printf ("9000\n");
			break;

		// ---------------------------- CHIP-8 Axxx instruction set ---------------------------- //
		case 0xA000: // Annn (CHIP-8)
			opc_chip8_ANNN();
			break;

		// ---------------------------- CHIP-8 Bxxx instruction set ---------------------------- //
		case 0xB000: // Bnnn (CHIP-8)
			printf ("B0000\n");
			break;

		// ---------------------------- CHIP-8 Cxxx instruction set ---------------------------- //
		case 0xC000: // Cxnn (CHIP-8)
			printf ("C0000\n");
			break;

		// ---------------------------- CHIP-8 Dxxx instruction set ---------------------------- //
		case 0xD000: // Dxyn (CHIP-8)
			printf ("D0000\n");
			break;

		// ---------------------------- CHIP-8 Exxx instruction set ---------------------------- //
		case 0xE000: // Exxx instruction set
			printf ("E0000\n");
			break;

		// ---------------------------- CHIP-8 Fxxx instruction set ---------------------------- //
		case 0xF000: // Fxxx instruction set
		{	
			unsigned short x;
			x = (Opcode & 0x0F00) >> 8;

			switch (  Opcode & 0x00FF )
			{

				// // Fx07 (CHIP-8)
				// case 0x0007:
				// 	opc_chip8_FX07(x);
				// 	break;

				// // Fx0A (CHIP-*)
				// case 0x000A:
				// 	opc_chip8_FX0A(x);
				// 	break;

				// // Fx15 (CHIP-8)
				// case 0x0015:
				// 	opc_chip8_FX15(x);
				// 	break;

				// // Fx18 (CHIP-8)
				// case 0x0018:
				// 	opc_chip8_FX18(x);
				// 	break;

				// // Fx1E (CHIP-8)
				// case 0x001E:
				// 	opc_chip8_FX1E(x);
				// 	break;

				// // Fx29 (CHIP-8)
				// case 0x0029:
				// 	opc_chip8_FX29(x);
				// 	break;

				// // Fx30 (SCHIP)
				// case 0x0030:
				// 	opc_schip_FX30(x);
				// 	break;

				// // Fx33 (CHIP-8)
				// case 0x0033:
				// 	opc_chip8_FX33(x);
				// 	break;

				// // Fx55 (CHIP-8)
				// case 0x0055:
				// 	opc_chip8_FX55(x);
				// 	break;

				// Fx65 (CHIP-8)
				case 0x0065:
					opc_chip8_FX65(x);
					break;

				// // FX75 (SCHIP)
				// case 0x0075:
				// 	opc_schip_FX75(x);
				// 	break;

				// // FX85 (SCHIP)
				// case 0x0085:
				// 	opc_schip_FX85(x);
				// 	break;

				// // Fx00 (ETI-660)
				// case 0x0000:
				// 	opc_chip8_ETI660_FX00(x);
				// 	break;

				default:
					printf("\t\tOpcode 0x%04X NOT IMPLEMENTED!!!!\n", Opcode);
					exit(2);
			}
			break;
		}

		default :
			printf ("Not implemented!\n");
  	}

}