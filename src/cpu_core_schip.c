#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_core_schip.h"

// // 00EE - RET
// // Return from a subroutine
// // The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
// // Need to incremente PC (PC+=2) after receive the value from Stack
// void opc_chip8_00EE() {
// 	PC = Stack[SP] + 2;
// 	SP --;
// 	if ( cpu_debug_mode )
// 		sprintf(cpu_debug_message, "CHIP-8 00EE: Return from a subroutine (PC=0x%04X)", PC);

// }



// SCHIP - 00FF
// Enable High-Res Mode (128 x 64 resolution)
// Enable SCHIP Mode
void opc_schip_00FF() {
	cpu_SCHIP_mode = true;
	cpu_SCHIP_LORES_mode = false;
	// scrollQuirks_00CN_00FB_00FC = false;

	// Set the clock to SCHIP
	CPU_CLOCK = 1500;

	// Set SCHIP Resolution
	display_SCREEN_WIDTH_X = 128;
	display_SCREEN_HEIGHT_Y = 64;

	// if Resize_Quirk_00FE_00FF {
	// 	// Clear the screen when changing graphic mode
	// 	Graphics = [128 * 64]byte{}
	// }

    SDL_SetWindowSize (window, display_SCREEN_WIDTH_X * display_SCALE, display_SCREEN_HEIGHT_Y * display_SCALE);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	PC += 2;

    if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "SCHIP 00FF: Enable high res (128 x 64) mode");

}