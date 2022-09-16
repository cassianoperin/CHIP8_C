#include <stdio.h>
#include <string.h>
#include "constant.h"

// Quirks needed by specific games
void Handle_legacy_opcodes(char *game_signature) {

	// ------------------------------ Official Qwirks ------------------------------ //

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
	if ( !strcmp(game_signature, "12245370616365466967+250532") ) {
		FX1E_spacefight2091 = true;
		printf("FX1E undocumented feature enabled.\n");
	}

	// Enable undocumented FX1E feature needed by sctest_12
	// SCHIP Test Program "sctest_12 (SC Test.ch8)"
	if ( !strcmp(game_signature, "12122054726F6E697820+49853") ) {
		FX1E_spacefight2091 = true;
		printf("FX1E undocumented feature enabled.\n");
	}

	// Enable Pixel Wrap Fix for Bowling game
	// Game: "Bowling [Gooitzen van der Wal]"
	if ( !strcmp(game_signature, "63146400255E600525B4+110648") ) {
		DXYN_bowling_wrap = true;
		printf("DXYN pixel wrap fix enabled.\n");
	}


	// ------------------------------- Other Qwirks -------------------------------- //

	// Enable Low Res 16x16 Pixel Draw in Robot.ch8 DEMO
	// SCHIP Demo: "Robot"
	if ( !strcmp(game_signature, "00FEA23A60006100620F+7720") ) {
		DXY0_loresWideSpriteQuirks = true;
		printf("DXY0 SCHIP Low Res 16x16 Pixel fix enabled.\n");
	}

	// This game uses 64x32 screen size
	// CHIP-8 ETI-660 Hybrid: "Pong"
	if ( !strcmp(game_signature, "6A026B0C6C3F6D0CA6EA+25121") ) {
		ETI660_64x32_screen = true;
		printf("ETI-660 Quirk 64 x 32 resolution Enabled.\n");
		SizeX = 64;
		SizeY = 32;
	}

	// // Enable slow key press
	// // CHIP-8 Game "Addition Problems [Paul C. Moews]"
	// if (game_signature == "ccccc") {
	// 	Keyboard_slow_press = true;
	// }

}