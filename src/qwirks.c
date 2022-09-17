#include <stdio.h>
#include <string.h>
#include "qwirks.h"

// --------------------------------- External Variables --------------------------------- //
// Screen Size
extern unsigned char SizeX;
extern unsigned char SizeY;


// ---------------------------------- Global Variables ---------------------------------- //
// Legacy Opcodes and Quirks
bool Quirk_Memory_Legacy_Fx55_Fx65; 	// Enable original Chip-8 Fx55 and Fx65 opcodes (increases I)
										// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#fx55-and-fx65-store-and-load-memory
bool Quirk_Shifting_Legacy_8xy6_8xyE;	// Enable original Chip-8 8xy6 and 8xyE opcodes
										// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#8xy6-and-8xye-shift
bool Quirk_Spacefight2091_FX1E;			// FX1E undocumented feature needed by Spacefight 2091!
bool Quirk_Clipping_DXYN;				// DXYN sprite wrap in Bowling game
										// Sprites drawn at the bottom edge of the screen get clipped instead of wrapping around to the top of the screen.
										// When clipping is off, the test checks if sprites get rendered at the right coordinates on the other side of the screen.
										// This also tests that sprites drawn at coordinates of x > 63 and/or y > 31 are rendered at x % 64 and y % 32. If any of these checks fail, the test will show ERR
bool Quirk_Resize_SCHIP_00FE_00FF;		// Resize_Quirk_00FE_00FF - Clears the screen - Must be set to True always
bool Quirk_Scroll_SCHIP_00CN_00FB_00FC;	// Shift only 2 lines
bool Quirk_ETI660_64x32_screen;			// Enable screen adjustment to 64x32 instead of default 64x48 ETI-660 HW
bool Quirk_Jump_with_offset_Bnnn;		// Bnnn behavior in some CHIP-48 and SUPER-CHIP that sum the value of V[x] instead of V[0]
										// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#bnnn-jump-with-offset
bool Quirk_LoResWideSprite_DXY0;		// DXY0_loresWideSpriteQuirks - Draws a 16x16 sprite even in low-resolution (64x32) mode, row-major
bool Quirk_VF_Reset_8XY1_8XY2_8XY3;		// The AND, OR and XOR opcodes (8XY1, 8XY2 and 8XY3) reset the flags register to zero
bool Quirk_ClockProgram_Fonts;			// To avoid glitches on FFFFF display, the memory used by SCHIP fonts can't be loaded
// bool	Keyboard_slow_press;			// Used by some programs that needs a slower key press rate


// -------------------------------------- Functions ------------------------------------- //
// Quirks needed by specific games
void Handle_legacy_opcodes(char *game_signature) {

	// Enable Fx55 and Fx65 legacy mode
	// Game "Animal Race [Brian Astle]"
	if ( !strcmp(game_signature, "6D0A6E02680E690BA5B5+103327") ) {
		Quirk_Memory_Legacy_Fx55_Fx65 = true;
		printf("Legacy mode Fx55/Fx65 enabled.\n");
	}

	// // Enable 2nd legacy mode
	// if (game_signature = "xxxxxxxxxxxxx") {
	// 	Legacy_8xy6_8xyE = true;
	// 	printf("Legacy mode 8xy6/8xyE enabled.\n");
	// }

	// Enable undocumented FX1E feature needed by Spacefight 2091!
	// Game "Spacefight 2091 [Carsten Soerensen, 1992].ch8"
	if ( !strcmp(game_signature, "12245370616365466967+250532") ) {
		Quirk_Spacefight2091_FX1E = true;
		printf("FX1E undocumented feature enabled.\n");
	}

	// Enable undocumented FX1E feature needed by sctest_12
	// SCHIP Test Program "sctest_12 (SC Test.ch8)"
	if ( !strcmp(game_signature, "12122054726F6E697820+49853") ) {
		Quirk_Spacefight2091_FX1E = true;
		printf("FX1E undocumented feature enabled.\n");
	}

	// Enable Pixel Wrap Fix for Bowling game
	// Game: "Bowling [Gooitzen van der Wal]"
	if ( !strcmp(game_signature, "63146400255E600525B4+110648") ) {
		Quirk_Clipping_DXYN = true;
		printf("DXYN pixel wrap fix enabled.\n");
	}

	// Enable Low Res 16x16 Pixel Draw in Robot.ch8 DEMO
	// SCHIP Demo: "Robot"
	if ( !strcmp(game_signature, "00FEA23A60006100620F+7720") ) {
		Quirk_LoResWideSprite_DXY0 = true;
		printf("DXY0 SCHIP Low Res 16x16 Pixel fix enabled.\n");
	}

	// This game uses 64x32 screen size
	// CHIP-8 ETI-660 Hybrid: "Pong"
	if ( !strcmp(game_signature, "6A026B0C6C3F6D0CA6EA+25121") ) {
		Quirk_ETI660_64x32_screen = true;
		printf("ETI-660 Quirk 64 x 32 resolution Enabled.\n");
		SizeX = 64;
		SizeY = 32;
	}

	// Set the quirks necessary for chip8-test-suite.ch8"
	// https://github.com/Timendus/chip8-test-suite#quirks-test
	if ( !strcmp(game_signature, "00E061016008AB0CD01F+320731") ) {
		Quirk_Jump_with_offset_Bnnn		= false;	// Jumping
		Quirk_Memory_Legacy_Fx55_Fx65	= true;		// Memory
		Quirk_Shifting_Legacy_8xy6_8xyE	= true;		// Shifting
		Quirk_Clipping_DXYN				= true;		// Clipping
		Quirk_VF_Reset_8XY1_8XY2_8XY3	= true;		// VF Reset
		// Disp, Wait	
		printf("Jumping, Memory, Shifting, Clipping and VF Reset Quirks enabled.\n");

	}

	// Do not load SCHIP fonts to avoid garbage after FFFFFF clock
	// CHIP8 Program: "Clock Program [Bill Fisher, 1981].ch8""
	if ( !strcmp(game_signature, "F10AF20AF30AF40AF50A+27721") ) {
		Quirk_ClockProgram_Fonts = true;
		printf("Clock Program Quirk Enabled.\n");
	} else {
		printf("FODEU.\n");
	}

	// Bnnn behavior in some CHIP-48 and SUPER-CHIP that sum the value of V[x] instead of V[0]
	// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#bnnn-jump-with-offset
	// Not used yet
	// if ( !strcmp(game_signature, "xxx") ) {
	// 	Bnnn_jump_with_offset	= false;
	// }

	// Set the quirks necessary for chip8-test-suite.ch8"
	// https://github.com/Timendus/chip8-test-suite#quirks-test
	// if (game_signature == "xxx") {
	// 	Keyboard_slow_press = true;
	// }

}