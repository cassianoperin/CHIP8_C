#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include "constant.h"

// Legacy Opcodes and Quirks
bool	Legacy_Fx55_Fx65 = false;          		// Enable original Chip-8 Fx55 and Fx65 opcodes (increases I)
bool	Legacy_8xy6_8xyE = false;          	 	// Enable original Chip-8 8xy6 and 8xyE opcodes
bool	FX1E_spacefight2091 = false;       	 	// FX1E undocumented feature needed by Spacefight 2091!
bool	DXYN_bowling_wrap = false;         	 	// DXYN sprite wrap in Bowling game
bool	Resize_Quirk_00FE_00FF = true;			// Resize_Quirk_00FE_00FF - Clears the screen - Must be set to True always
bool	DXY0_loresWideSpriteQuirks = false;		// DXY0_loresWideSpriteQuirks - Draws a 16x16 sprite even in low-resolution (64x32) mode, row-major
bool	scrollQuirks_00CN_00FB_00FC = false;	// Shift only 2 lines
bool	ETI660_64x32_screen = false;			// Enable screen adjustment to 64x32 instead of default 64x48 ETI-660 HW
bool	Keyboard_slow_press = false;			// Used by some programs that needs a slower key press rate


void Handle_legacy_opcodes(char *game_signature) {

	// Quirks needed by specific games

	// Enable Fx55 and Fx65 legacy mode
	// Game "Animal Race [Brian Astle]"
	if ( !strcmp(game_signature, "6D0A6E02680E690BA5B5+103327") ) {
		Legacy_Fx55_Fx65 = true;
		printf("Legacy mode Fx55/Fx65 enabled.\n");
	}

	// // Enable 2nd legacy mode
	// if (game_signature = "xxxxxxxxxxxxx") {
	// 	Legacy_8xy6_8xyE = true;
	// 	printf("Legacy mode 8xy6/8xyE enabled.\n");
	// }

	// Enable undocumented FX1E feature needed by Spacefight 2091!
	// Game "Spacefight 2091 [Carsten Soerensen, 1992].ch8"
	// if (game_signature = "xxxxxxx") {
	// 	FX1E_spacefight2091 = true;
	// 	printf("FX1E undocumented feature enabled.\n");
	// }

	// Enable undocumented FX1E feature needed by sctest_12
	// SCHIP Test Program "sctest_12 (SC Test.ch8)"
	if ( !strcmp(game_signature, "12122054726F6E697820+49853") ) {
		FX1E_spacefight2091 = true;
		printf("FX1E undocumented feature enabled.\n");
	}

	// // Enable Pixel Wrap Fix for Bowling game
	// // Game: "Bowling [Gooitzen van der Wal]"
	// if (game_signature = "ccc") {
	// 	DXYN_bowling_wrap = true;
	// 	printf("DXYN pixel wrap fix enabled.\n");
	// }

	// // Enable Low Res 16x16 Pixel Draw in Robot.ch8 DEMO
	// // SCHIP Demo: "Robot"
	// if (game_signature == "ccc") {
	// 	DXY0_loresWideSpriteQuirks = true;
	// 	printf("DXY0 SCHIP Low Res 16x16 Pixel fix enabled.\n");
	// }

	// // This game uses 64x32 screen size
	// // CHIP-8 ETI-660 Hybrid: "Pong"
	// if (game_signature == "cccc") {
	// 	ETI660_64x32_screen = true;
	// 	printf("ETI-660 Quirk 64 x 32 resolution Enabled.\n");
	// 	SizeX = 64;
	// 	SizeY = 32;
	// }

	// // Enable slow key press
	// // CHIP-8 Game "Addition Problems [Paul C. Moews]"
	// if (game_signature == "ccccc") {
	// 	Keyboard_slow_press = true;
	// }

}