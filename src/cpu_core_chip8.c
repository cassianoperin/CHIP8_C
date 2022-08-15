#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "constant.h"

extern bool drawFlag;
extern bool drawFlagCounter;
extern bool SCHIP;
extern bool SCHIP_LORES;

// ---------------------------- CHIP-8 0xxx instruction set ---------------------------- //

// // 0NNN
// // Execute RCA 1802 machine language routine at address NNN
// func opc_chip8_0NNN() {
// 	// Not needed by any game, just for documentation
// }

// 00E0 - CLS
// Clear the display.
void opc_chip8_00E0() {
    memset(pixels, 0x00, sizeof(pixels));
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 00E0: Clear the display");
		printf("\t\t%s\n" , OpcMessage);
	}
}

// 00EE - RET
// Return from a subroutine
// The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
// Need to incremente PC (PC+=2) after receive the value from Stack
void opc_chip8_00EE() {
	PC = Stack[SP] + 2;
	SP --;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 00EE: Return from a subroutine (PC=0x%04X)", PC);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// // ---------------------------- CHIP-8 1xxx instruction set ---------------------------- //

// 1nnn - JP addr
// Jump to location nnn.
// The interpreter sets the program counter to nnn.
void opc_chip8_1NNN() {
	PC = Opcode & 0x0FFF;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 1nnn: Jump to location 0x%02X", Opcode & 0x0FFF);
		printf("\t\t%s\n" , OpcMessage);
	}
}

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


// ---------------------------- CHIP-8 3xxx instruction set ---------------------------- //

// 3xnn - SE Vx, byte
// Skip next instruction if Vx = NN.
// The interpreter compares register Vx to nn, and if they are equal, increments the program counter by 2.
void opc_chip8_3XNN() {
    unsigned char x, nn;

	x = (Opcode & 0x0F00) >> 8;
	nn = (unsigned char)Opcode & 0x00FF;
	if ( V[x] == nn ) {
		PC += 4;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 3xnn: V[x(%d)]:(0x%02X) = nn(0x%02X), skip one instruction", x, V[x], nn);
			printf("\t\t%s\n" , OpcMessage);
		}
	} else {
		PC += 2;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 3xnn: V[x(%d)]:(0x%02X) != nn(0x%02X), do NOT skip one instruction", x, V[x], nn);
			printf("\t\t%s\n" , OpcMessage);
		}
	}
}

// // ---------------------------- CHIP-8 4xxx instruction set ---------------------------- //

// 4xnn - SNE Vx, byte
// Skip next instruction if Vx != nn.
// The interpreter compares register Vx to nn, and if they are not equal, increments the program counter by 2.
void opc_chip8_4XNN() {
    unsigned char x, nn;

	x = (Opcode & 0x0F00) >> 8;
	nn = (unsigned char)Opcode & 0x00FF;
	if ( V[x] != nn ) {
		PC += 4;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 4xnn: V[x(%d)]: 0x%02X != nn(0x%02X), skip one instruction", x, V[x], nn);
			printf("\t\t%s\n" , OpcMessage);
		}
	} else {
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 4xnn: V[x(%d)]: 0x%02X = nn(0x%02X), DO NOT skip one instruction", x, V[x], nn);
			printf("\t\t%s\n" , OpcMessage);
		}
		PC += 2;
	}
}

// ---------------------------- CHIP-8 5xxx instruction set ---------------------------- //

// 5xy0 - SE Vx, Vy
// Skip next instruction if Vx = Vy.
// The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
void opc_chip8_5XY0() {
	unsigned char x, y;

	x = (Opcode & 0x0F00) >> 8;
	y = (Opcode & 0x00F0) >> 4;

	if ( V[x] == V[y] ){
		PC += 4;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 5xy0: V[x(%d)]:%d EQUAL V[y(%d)]:%d, SKIP one instruction", x, V[x], y, V[y]);
			printf("\t\t%s\n" , OpcMessage);
		}
	} else {
		PC += 2;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 5xy0: V[x(%d)]:%d NOT EQUAL V[y(%d)]:%d, DO NOT SKIP one instruction", x, V[x], y, V[y]);
			printf("\t\t%s\n" , OpcMessage);
		}
	}
}

// ---------------------------- CHIP-8 6xxx instruction set ---------------------------- //

// 6xnn - LD Vx, byte
// Set Vx = nn.
// The interpreter puts the value nn into register Vx.
void opc_chip8_6XNN() {
    unsigned char x, nn;

	x = (Opcode & 0x0F00) >> 8;
	nn = (char)Opcode;

	V[x] = nn;
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 6xnn: Set V[x(%d)] = 0x%02X", x, nn);
		printf("\t\t%s\n" , OpcMessage);
	}
}


// ---------------------------- CHIP-8 7xxx instruction set ---------------------------- //

// 7xnn - ADD Vx, byte
// Set Vx = Vx + nn.
// Adds the value nn to the value of register Vx, then stores the result in Vx.
void opc_chip8_7XNN() {
	unsigned char x, nn;

	x = (Opcode & 0x0F00) >> 8;
	nn = (unsigned char)Opcode;

	V[x] += nn;

	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 7xnn: Add the value nn(%d) to V[x(%d)]", nn, x);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// ---------------------------- CHIP-8 8xxx instruction set ---------------------------- //

// 8xy0 - LD Vx, Vy
// Set Vx = Vy.
// Stores the value of register Vy in register Vx.
void opc_chip8_8XY0(unsigned char x, unsigned char y) {
	V[x] = V[y];
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy0: Set V[x(%d)] to the value of V[y(%d)] = 0x%02X", x, y, V[y]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// 8xy1 - Set Vx = Vx OR Vy.
// Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corresponding bits from two values,
// and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
void opc_chip8_8XY1(unsigned char x, unsigned char y) {
	V[x] |= V[y];
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy1: Set V[x(%d)]:%d OR V[y(%d)]:%d", x, V[x], y, V[y]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// 8xy2 - AND Vx, Vy
// Set Vx = Vx AND Vy.
// Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corresponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
void opc_chip8_8XY2(unsigned char x, unsigned char y) {
	V[x] &= V[y];
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy2: Set V[x(%d)] to the result of V[x(%d)]:(0x%02x) AND V[y(%d)]:(0x%02X) = 0x%02X", x, x, V[x], y, V[y], V[x] &= V[y]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// 8xy3 - XOR Vx, Vy
// Set Vx = Vx XOR Vy.
// Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corresponding bits from two values,
// and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
void opc_chip8_8XY3(unsigned char x, unsigned char y) {
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy3: Set V[x(%d)]:%d XOR V[y(%d)]:%d", x, V[x], y, V[y]);
		printf("\t\t%s\n" , OpcMessage);
	}
	V[x] ^= V[y];
	PC += 2;
}

// 8xy4 - ADD Vx, Vy
// Set Vx = Vx + Vy, set VF = carry.
// The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0.
// Only the lowest 8 bits of the result are kept, and stored in Vx.
// *** Flag needs to be set AFTER the ADD
void opc_chip8_8XY4(unsigned char x, unsigned char y) {

	// Test the new value and set the flag
	unsigned char sum = V[x] + V[y];	// Need in case of overflows (keep number between 0-255)
	unsigned char Vx_original = V[x];	// Necessary once the flag will be set AFTER the ADD

	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy4: Set V[x(%d)] = V[x(%d)]: 0x%02X + V[y(%d)]: 0x%02X", x, x, V[x], y, V[y]);
		printf("\t\t%s\n" , OpcMessage);
	}
	// Old implementation, sum values, READ THE DOCS IN CASE OF PROBLEMS
	V[x] += V[y];

	if ( sum < Vx_original) {
		V[0xF] = 1;
	} else {
		V[0xF] = 0;
	}

	PC += 2;
}

// 8xy5 - SUB Vx, Vy
// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
// *** Flag needs to be set AFTER the ADD
void opc_chip8_8XY5(unsigned char x, unsigned char y) {

	unsigned char Vx_original = V[x];	// Necessary once the flag will be set AFTER the ADD

    if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy5: Set V[x(%d)] = V[x(%d)]: 0x%02X - V[y(%d)]: 0x%02X", x, x, V[x], y, V[y]);
		printf("\t\t%s\n" , OpcMessage);
	}

	V[x] -= V[y];

	// Now update the flag
	if ( Vx_original >= V[y] ) {
		V[0xF] = 1;
	} else {
		V[0xF] = 0;
	}

	PC += 2;
}

// 8xy6 - SHR Vx {, Vy}
// Set Vx = Vx SHR 1.
// If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2 (SHR).
// Original Chip8 INCREMENT I in this instruction
void opc_chip8_8XY6(unsigned char x, unsigned char y) {
	V[0xF] = V[x] & 0x01;

	if ( Legacy_8xy6_8xyE ) {
		V[x] = V[y] >> 1;
	} else {
		V[x] = V[x] >> 1;
	}

	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy6: Set V[x(%d)] SHIFT RIGHT 1 = 0x%02X", x, V[x]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// 8xy7 - SUBN Vx, Vy
// Set Vx = Vy - Vx, set VF = NOT borrow.
// If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
// *** Update the flag AFTER the SUBN with the V[x] RESULT and not original
void opc_chip8_8XY7(unsigned char x, unsigned char y) {

	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xy7: Set V[x(%d)]:%d = V[y(%d)]:%d - V[x(%d)]:%d\t\t = %d", x, V[x], y, V[y], x, V[x], V[y] - V[x]);
		printf("\t\t%s\n" , OpcMessage);
	}
	V[x] = V[y] - V[x];

	// Now update the flag
	if ( V[x] > V[y] ) {
		V[0xF] = 0;
	} else {
		V[0xF] = 1;
	}

	PC += 2;
}

// 8xyE - SHL Vx {, Vy}
// Set Vx = Vx SHL 1.
// If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
// *** The flag must be updated with the original V[x] value AFTER the SHL
void opc_chip8_8XYE(unsigned char x, unsigned char y) {

	unsigned char Vx_original = V[x];	// Necessary once the flag will be set AFTER the SHL

	if ( Legacy_8xy6_8xyE ) {
		V[x] = V[y] << 1;
	} else {
		V[x] = V[x] << 1;
	}

	// Now update the flag
	V[0xF] = Vx_original >> 7; // Set V[F] to the Most Important Bit

	PC += 2;
	
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 8xyE: Set V[x(%d)] SHIFT LEFT 1 =  0x%02X ", x, V[x]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// ---------------------------- CHIP-8 9xxx instruction set ---------------------------- //

// // 9xy0 - SNE Vx, Vy
// // Skip next instruction if Vx != Vy.
// // The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
void opc_chip8_9XY0() {
    unsigned char x,y;

	x = (Opcode & 0x0F00) >> 8;
	y = (Opcode & 0x00F0) >> 4;

	if ( V[x] != V[y] ) {
		PC += 4;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 9xy0: V[x(%d)]:%02X != V[y(%d)]: 0x%02X, SKIP one instruction", x, V[x], y, V[y]);
			printf("\t\t%s\n" , OpcMessage);
		}
	} else {
		PC += 2;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 9xy0: V[x(%d)]:%02X = V[y(%d)]: 0x%02X, DO NOT SKIP one instruction", x, V[x], y, V[y]);
			printf("\t\t%s\n" , OpcMessage);
		}
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



// // ---------------------------- CHIP-8 Bxxx instruction set ---------------------------- //

// Bnnn - JP V0, addr
// Jump to location nnn + V0.
// The program counter is set to nnn plus the value of V0.
void opc_chip8_BNNN() {
	unsigned short nnn = Opcode & 0x0FFF;
	PC = nnn + (unsigned short)V[0];
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Bnnn: Jump to location nnn(%d) + V[0(%d)]", nnn, V[0]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// // ---------------------------- CHIP-8 Cxxx instruction set ---------------------------- //

// Cxnn - RND Vx, byte
// Set Vx = random byte AND nn.
// The interpreter generates a random number from 0 to 255, which is then ANDed with the value nn. The results are stored in Vx. See instruction 8xy2 for more information on AND.
void opc_chip8_CXNN() {
	unsigned short x;
	unsigned char nn;
	x = (unsigned short)(Opcode&0x0F00) >> 8;
	nn = Opcode & 0x00FF;

	V[x] = (rand() % 255) & nn;

	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Cxnn: V[x(%d)] = %d (random byte AND nn(%d)) = %d", x, V[x], nn, V[x]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// ---------------------------- CHIP-8 Dxxx instruction set ---------------------------- //

// Dxyn - DRW Vx, Vy, nibble
// Draw n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void opc_chip8_DXYN() {
	// // Draw in Chip-8 Low Resolution mode
    unsigned short x, y, n, byte, gpx_position;
    unsigned char sprite;

	x = (Opcode & 0x0F00) >> 8;
	y = (Opcode & 0x00F0) >> 4;
    n = (Opcode & 0x000F);
    // Check if they need to be initialized //
    byte = 0;
    gpx_position = 0;
    sprite = 0;

	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Dxyn: DRAW GRAPHICS - Address I: %d Position V[x(%d)]: %d V[y(%d)]: %d N: %d", I, x, V[x], y, V[y], n);
		printf("\t\t%s\n" , OpcMessage);
	}

	// Clean the colision flag
	V[0xF] = 0;

	// Check if y is out of range and apply module to fit in screen
	if ( V[y] >= SizeY ) {
        if (SizeY != 0) {
            V[y] = V[y] % SizeY;
            if ( Debug ) {
                printf("\t\tV[y] >= %d, modulus applied", SizeY);
            }
        }
	}

	// Check if y is out of range and apply module to fit in screen
	if ( V[x] >= SizeX ) {
        if (SizeX != 0) {
            V[x] = V[x] % SizeX;
            if ( Debug ) {
                printf("\t\tV[x] >= %d, modulus applied", SizeX);
            }
        }
	}

	// Fix for Bowling game where the pins wrap the screen
	if ( DXYN_bowling_wrap ) {
		if ( V[x] + (unsigned char)n > SizeX +1 ) {
			n = (SizeX - 1) - (unsigned short)V[x];
		}
	}

	// Translate the x and Y to the Graphics Vector
	gpx_position = (unsigned short)V[x] + ( SizeX * (unsigned short)V[y] );

	// Print N Bytes from address I in V[x]V[y] position of the screen
	for ( byte = 0 ; byte < n ; byte++ ) {

		// Set the sprite
		sprite = Memory[I + byte];

		// Always print 8 bits
        unsigned short bit, bit_value, gfx_index;
		for ( bit = 0; bit < 8 ; bit++ ) {
			// Get the value of the byte
			bit_value = (unsigned short)sprite >> (7 - bit) & 1;

			// Set the index to write the 8 bits of each pixel
			gfx_index = (unsigned short)gpx_position + (unsigned short)bit + (byte*SizeX);

			// If tryes to draw bits outside the vector size, ignore
			if ( gfx_index >= SizeX * SizeY ) {
				if ( Debug ) {
					printf("\n\n\nGraphics: Bigger than 2048 or 8192\n\n\n\n");
				}
				continue;
			}

			// // If bit=1, test current graphics[index], if is already set, mark v[F]=1 (collision)
			// if ( bit_value  == 1 ) {
			// 	// Set colision case graphics[index] is already 1
			// 	if ( pixels[gfx_index] == PIXEL_ON_COLOR ) {
			// 		V[0xF] = 1;
			// 	}
			// 	// After, XOR the graphics[index] (DRAW)
			// 	// pixels[gfx_index] ^= 1;
			// 	pixels[gfx_index] = PIXEL_ON_COLOR;


						// If bit=1, test current graphics[index], if is already set, mark v[F]=1 (collision)
			if ( bit_value  == 1 ) {
				// Set colision case graphics[index] is already 1
				if ( pixels[gfx_index] == PIXEL_ON_COLOR ) {
					V[0xF] = 1;
					pixels[gfx_index] = PIXEL_OFF_COLOR; 
				} else {
          			pixels[gfx_index] = PIXEL_ON_COLOR;
				}
				// After, XOR the graphics[index] (DRAW)
				// pixels[gfx_index] ^= 1;
				// pixels[gfx_index] = PIXEL_ON_COLOR;

                
			}


		}

	}
                // pixels[100] = PIXEL_ON_COLOR;


	PC += 2;
	drawFlag = true;
	drawFlagCounter ++;

//   cpu->v[CARRY_REGISTER] = 0;
//   for (int y = 0; y < n; y++) {
//     for (int x = 0; x < 8; x++) {
//       uint8_t pixel = Memory[I + y];
//       if (pixel & (0x80 >> x)) {
//         int index = (V[x] + x) % 64 + ((V[y] + y) % 32) * 64;
//         if (pixels[index] == PIXEL_ON_COLOR) {
//         //   cpu->v[CARRY_REGISTER] = 1;
//           pixels[index] = PIXEL_OFF_COLOR;
//         } else {
//           pixels[index] = PIXEL_ON_COLOR;
//         }
//         drawFlag = true;
//       }
//     }

    // }

}

// ---------------------------- CHIP-8 Exxx instruction set ---------------------------- //

// Ex9E - SKP Vx
// Skip next instruction if key with the value of Vx is pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
void opc_chip8_EX9E(unsigned char x) {

	// If Key number is bigger than 16, fix it (Ex.: Breakfree game)
	if ( V[x] >= sizeof(Key) ) {
		V[x] = V[x] - 16;
		printf("\n%d\n",x);
	}

	if ( Key[V[x]] == 1 ) {
		PC += 4;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 Ex9E: Key[%d] pressed, skip one instruction", V[x]);
			printf("\t\t%s\n" , OpcMessage);
		}
	} else {
		PC += 2;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 Ex9E: Key[%d] NOT pressed, continue", V[x]);
			printf("\t\t%s\n" , OpcMessage);
		}
	}
}

// ExA1 - SKNP Vx
// Skip next instruction if key with the value of Vx is not pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
void opc_chip8_EXA1(unsigned char x) {
	if ( Key[V[x]] == 0 ) {
		PC += 4;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 ExA1: Key[%d] NOT pressed, skip one instruction", V[x]);
			printf("\t\t%s\n" , OpcMessage);
		}
	} else {
		// Key[V[x]] = 0;
		PC += 2;
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 ExA1: Key[%d] pressed, continue\n", V[x]);
			printf("\t\t%s\n" , OpcMessage);
		}
	}
}



// ---------------------------- CHIP-8 Fxxx instruction set ---------------------------- //

// Fx07 - LD Vx, DT
// Set Vx = delay timer value.
// The value of DT is placed into Vx.
void opc_chip8_FX07(unsigned char x) {
	V[x] = DelayTimer;
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Fx07: Set V[x(%d)] with value of DelayTimer(%02X)", x, DelayTimer);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// Fx0A - LD Vx, K
// Wait for a key press, store the value of the key in Vx.
// All execution stops until a key is pressed, then the value of that key is stored in Vx.
void opc_chip8_FX0A(unsigned char x) {
	bool pressed = false;
	unsigned int i;

	for ( i = 0 ; i < sizeof(Key) ; i++ ) {
		if (Key[i] == 1) {
			V[x] = (unsigned char)i;
			pressed = true;
			PC +=2;
			if ( Debug ) {
				sprintf(OpcMessage, "CHIP-8 Fx0A: Wait for a key (Key[%d]) press = (PRESSED)", i);
				printf("\t\t%s\n" , OpcMessage);
			}
			// Stop after find the first key pressed
			break;
		}
	}
	if ( !pressed ) {
		if ( Debug ) {
			sprintf(OpcMessage, "CHIP-8 Fx0A: Wait for a key press = (NOT PRESSED)");
			printf("\t\t%s\n" , OpcMessage);
		}
	}
}

// Fx15 - LD DT, Vx
// Set delay timer = Vx.
// DT is set equal to the value of Vx.
void opc_chip8_FX15(unsigned char x) {
	DelayTimer = V[x];
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Fx15: Set delay timer = V[x(%d)]: 0x%02X", x, V[x]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// Fx18 - LD ST, Vx
// Set sound timer = Vx.
// ST is set equal to the value of Vx.
void opc_chip8_FX18(unsigned char x) {
	SoundTimer = V[x];
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Fx18: Set sound timer = V[x(%d)]:%d",x, V[x]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// Fx1E - ADD I, Vx
// Set I = I + Vx.
// The values of I and Vx are added, and the results are stored in I.
// ***
// Check FX1E (I = I + VX) buffer overflow. If buffer overflow, register
// VF must be set to 1, otherwise 0. As a result, register VF not set to 1.
// This undocumented feature of the Chip-8 and used by Spacefight 2091!
void opc_chip8_FX1E(unsigned char x) {
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Fx1E: Add the value of V[x(%d)]: 0x%02X to I: (0x%04X)",x, V[x], I);
		printf("\t\t%s\n" , OpcMessage);
	}

	// *** Implement the undocumented feature used by Spacefight 2091
	if ( FX1E_spacefight2091 ) {
		if ( I + (unsigned short)V[x] > 0xFFF ) { //4095 - Buffer overflow
			V[0xF] = 1;
			I = ( I + (unsigned short)V[x] ) - 4095;
		} else {
			V[0xF] = 0;
			I += (unsigned short)V[x];
		}
	// Normal opcode pattern
	} else {
		I += (unsigned short)V[x];
	}

	PC += 2;
}

// Fx29 - LD F, Vx
// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
void opc_chip8_FX29(unsigned char x) {
	// Load CHIP-8 font. Start from Memory[0]
	I = (unsigned short)V[x] * 5;
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Fx29: Set I(%X) = location of sprite for digit V[x(%d)]:%d (*5)", I, x, V[x]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// Fx33 - LD B, Vx
// BCD - Binary Code hexadecimal
// Store BCD representation of Vx in memory locations I, I+1, and I+2.
// set_BCD(Vx);
// Ex. V[x] = ff (maximum value) = 255
// memory[i+0] = 2
// memory[i+1] = 5
// memory[i+2] = 5
// % = modulus operator:
// 3 % 1 would equal zero (since 3 divides evenly by 1)
// 3 % 2 would equal 1 (since dividing 3 by 2 results in a remainder of 1).
void opc_chip8_FX33(unsigned char x) {
	Memory[I]   = V[x]  / 100;
	Memory[I+1] = (V[x] / 10)  % 10;
	Memory[I+2] = (V[x] % 100) % 10;
	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Fx33: Store BCD of V[x(%d)]:%d in memory locations I(%X):%d, I+1(%X):%d, and I+2(%X):%d", x, V[x], I, Memory[I], I+1, Memory[I+1], I+2, Memory[I+2]);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// Fx55 - LD [I], Vx
// Store registers V0 through Vx in memory starting at location I.
// The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
//
// Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.[d]
// In the original CHIP-8 implementation, and also in CHIP-48, I is left incremented after this instruction had been executed. In SCHIP, I is left unmodified.
void opc_chip8_FX55(unsigned char x) {
    unsigned char i;
	for ( i = 0; i <= x; i++ ) {
		Memory[I+i] = V[i];
	}
	PC += 2;

	// If needed, run the original Chip-8 opcode (not used in recent games)
	if ( Legacy_Fx55_Fx65 ) {
		I = I + x + 1;
	}

	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 Fx55: Put registers V[0] through V[x(0x%02X)] in memory starting at location I(0x%04X)",x, I);
		printf("\t\t%s\n" , OpcMessage);

        for ( i = 0 ; i <= x ; i ++ ) {
			printf("\t\t Memory[%04X] = 0x%02X\n", I+i, Memory[I+i]);
		}
	}
}


// Fx65 - LD Vx, [I]
// Read registers V0 through Vx from memory starting at location I.
// The interpreter reads values from memory starting at location I into registers V0 through Vx.
//// I is set to I + X + 1 after operation²
//// ² Erik Bryntse’s S-CHIP documentation incorrectly implies this instruction does not modify
//// the I register. Certain S-CHIP-compatible emulators may implement this instruction in this manner.
void opc_chip8_FX65(unsigned char x) {

	unsigned char i;

	for ( i = 0; i <= x; i++ ) {
		V[i] = Memory[I+i];
	}

	PC += 2;

	// If needed, run the original Chip-8 opcode (not used in recent games)
	if ( Legacy_Fx55_Fx65 ) {
		I = I + x + 1;
	}

	if ( Debug)  {

		sprintf(OpcMessage, "CHIP-8 Fx65: Set registers V[0] through V[x(%d)] from memory starting at location I(0x%04X)",x, I);
		printf("\t\t%s\n" , OpcMessage);

		for ( i = 0 ; i <= x ; i ++ ) {
			printf("\t\t V[%02X] = 0x%02X\n", i, V[i]);
		}
	}
}

// ---------------------------- CHIP-8 undocumented instructions ---------------------------- //

// 02D8
// NON DOCUMENTED OPCODED, USED BY DEMO CLOCK Program
// LDA 02, I // Load from memory at address I into V[00] to V[02]
void opc_chip8_ND_02D8() {
	unsigned char x;

	x = (Opcode & 0x0F00) >> 8;

	if ( x != 2 ) {
		//Map if this opcode can receive a different value here
		printf("\nProposital exit to map usage of 02D8 opcode\n");
		exit(2);
	}

	V[0] = (unsigned char)I;
	V[1] = (unsigned char)I + 1;
	V[2] = (unsigned char)I + 2;

	PC += 2;
	if ( Debug ) {
		sprintf(OpcMessage, "CHIP-8 02DB (NON DOCUMENTED): Load from memory at address I(%d) into V[0]= %d, V[1]= %d and V[2]= %d.", I, I , I+1, I+2);
		printf("\t\t%s\n" , OpcMessage);
	}
}

// // 02E4
// // NON DOCUMENTED OPCODED, USED BY CHIP-8 Tic-Tac-Toe ([AUD_2464_09_B41_ID23_01] sound program
// // LDF I, V[02] // Load into I the address of the 8x5 font with index as value of V[02].
// func opc_chip8_ND_02E4() {
// 	I = uint16(Memory[V[2]])
// 	PC+=2
// }

// ---------------- CHIP-8 undocumented instructions found on internet for future needs ---------------- //
// // 02A6: 22D4
// CALL 02D4 // Call sub-routine at address 02D4 (724) in memory.
//
// // 02D4: A2F2
// LD I, 02F2 // Load 02F2 (754 in decimal) into I.
//
// // 02D6: FE33
// BCD V[0E] // Load into memory at address I the BCD value of V[0E].
//
// // Value of V[0E]: 00 (0)
// // Hundreds: 0
// // Tens    : 0
// // Units   : 0
//
// // I: 02F2 (754)
// // mem[02F2]: 00 (0)
// // mem[02F3]: 00 (0)
// // mem[02F4]: 00 (0)
//
// // 02D8: F265
// LDA 02, I // Load from memory at address I into V[00] to V[02].
//
// // V[00]: 00 (0)
// // V[01]: 00 (0)
// // V[02]: 00 (0)
//
// // 02DA: F129
// LDF I, V[01] // Load into I the address of the 8x5 font with index as value of V[01].
//
// // 02DC: 6414
// LD V[04], 0014 // Load 0014 (20) into V[04].
//
// // 02DE: 6500
// LD V[05], 0000 // Load 0000 (0) into V[05].
//
// // 02E0: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=14 (20) and y=00 (0).
//
// // 02E2: 7415
// ADD V[04], 0015 // Add 0015 (21) into V[04].
//
// // 02E4: F229
// LDF I, V[02] // Load into I the address of the 8x5 font with index as value of V[02].
//
// // 02E6: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=29 (41) and y=00 (0).
//
// // 02E8: 00EE
// RET // Return from sub-routine.
//
// // 02A8: 8E34
// ADD V[0E], V[03] // Add V[03] into V[0E].
//
// // 02AA: 22D4
// CALL 02D4 // Call sub-routine at address 02D4 (724) in memory.
//
// // 02D4: A2F2
// LD I, 02F2 // Load 02F2 (754 in decimal) into I.
//
// // 02D6: FE33
// BCD V[0E] // Load into memory at address I the BCD value of V[0E].
//
// // Value of V[0E]: 0A (10)
// // Hundreds: 0
// // Tens    : 1
// // Units   : 0
//
// // I: 02F2 (754)
// // mem[02F2]: 00 (0)
// // mem[02F3]: 01 (1)
// // mem[02F4]: 00 (0)
//
// // 02D8: F265
// LDA 02, I // Load from memory at address I into V[00] to V[02].
//
// // V[00]: 00 (0)
// // V[01]: 01 (1)
// // V[02]: 00 (0)
//
// // 02DA: F129
// LDF I, V[01] // Load into I the address of the 8x5 font with index as value of V[01].
//
// // 02DC: 6414
// LD V[04], 0014 // Load 0014 (20) into V[04].
//
// // 02DE: 6500
// LD V[05], 0000 // Load 0000 (0) into V[05].
//
// // 02E0: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=14 (20) and y=00 (0).
//
// // 02E2: 7415
// ADD V[04], 0015 // Add 0015 (21) into V[04].
//
// // 02E4: F229
// LDF I, V[02] // Load into I the address of the 8x5 font with index as value of V[02].
//
// // 02E6: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=29 (41) and y=00 (0).
//
// // 02E8: 00EE
// RET // Return from sub-routine.