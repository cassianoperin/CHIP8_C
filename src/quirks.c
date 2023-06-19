#include <stdio.h>
#include <string.h>
#include "quirks.h"

// Quirks needed by specific games
void handle_legacy_opcodes(char *game_signature) {

	// Disable Fx55 and Fx65 legacy mode
	// Game "Astro Dodge [Revival Studios, 2008]"
	if ( !strcmp(game_signature, "12145245564956414C53+106009") ) {
		quirk_Memory_legacy_Fx55_Fx65 = false;
		printf("\nCHIP 8 Quirks:\nMemory:\t\tDisabled\n\n");
	}

	// Enable Fx55 and Fx65 legacy mode
	// Game "Animal Race [Brian Astle]"
	if ( !strcmp(game_signature, "6D0A6E02680E690BA5B5+103327") ) {
		quirk_Memory_legacy_Fx55_Fx65 = true;
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
		quirk_Spacefight2091_Fx1E = true;
		printf("FX1E undocumented feature enabled.\n");
	}

	// Enable undocumented FX1E feature needed by sctest_12
	// SCHIP Test Program "sctest_12 (SC Test.ch8)"
	if ( !strcmp(game_signature, "12122054726F6E697820+49853") ) {
		quirk_Spacefight2091_Fx1E = true;
		printf("FX1E undocumented feature enabled.\n");
	}

	// Enable Pixel Wrap Fix for Bowling game
	// Game: "Bowling [Gooitzen van der Wal]"
	if ( !strcmp(game_signature, "63146400255E600525B4+110648") ) {
		quirk_Clipping_Dxyn = true;
		printf("DXYN pixel wrap fix enabled.\n");
	}

	// Enable Low Res 16x16 Pixel Draw in Robot.ch8 DEMO
	// SCHIP Demo: "Robot"
	if ( !strcmp(game_signature, "00FEA23A60006100620F+7720") ) {
		quirk_LoRes_Wide_Sprite_Dxy0 = true;
		printf("DXY0 SCHIP Low Res 16x16 Pixel fix enabled.\n");
	}

	// This game uses 64x32 screen size
	// CHIP-8 ETI-660 Hybrid: "Pong"
	if ( !strcmp(game_signature, "6A026B0C6C3F6D0CA6EA+25121") ) {
		quirk_ETI660_64x32_screen = true;
		printf("ETI-660 Quirk 64 x 32 resolution Enabled.\n");
		display_SCREEN_WIDTH_X = 64;
		display_SCREEN_HEIGHT_Y = 32;
	}

	// Set the quirks necessary for chip8-test-suite.ch8 (v2)"
	// https://github.com/Timendus/chip8-test-suite#quirks-test
	if ( !strcmp(game_signature, "00E061016008AB0CD01F+320731") ) {
		// Chip8
		quirk_VF_Reset_8xy1_8xy2_8xy3	= true;		// VF Reset
		quirk_Memory_legacy_Fx55_Fx65	= true;		// Memory
		quirk_display_wait				= true;		// Display wait
		quirk_Clipping_Dxyn				= true;		// Clipping
		quirk_Shifting_legacy_8xy6_8xyE	= false;	// Shifting
		quirk_Jump_with_offset_Bnnn		= false;	// Jumping
		// SCHIP
		printf("\nCHIP 8 Quirks:\nVF Reset:\tEnabled\nMemory:\t\tEnabled\nDisplay Wait:\tEnabled\nClipping:\tEnabled\nShifting:\tDisabled\nJumping:\tDisabled\n\n");
	}

	// Set the quirks necessary for chip8-test-suite.ch8 (v4)"
	// 5-quirks.ch8
	// https://github.com/Timendus/chip8-test-suite
	if ( !strcmp(game_signature, "130C6000E0A112047001+150419") ) {
		// Chip8
		quirk_VF_Reset_8xy1_8xy2_8xy3	= true;		// VF Reset
		quirk_Memory_legacy_Fx55_Fx65	= true;		// Memory
		quirk_display_wait				= true;		// Display wait
		quirk_Clipping_Dxyn				= true;		// Clipping
		quirk_Shifting_legacy_8xy6_8xyE	= false;	// Shifting
		quirk_Jump_with_offset_Bnnn		= false;	// Jumping
		// SCHIP
		printf("\nCHIP 8 Quirks:\nVF Reset:\tEnabled\nMemory:\t\tEnabled\nDisplay Wait:\tEnabled\nClipping:\tEnabled\nShifting:\tDisabled\nJumping:\tDisabled\n\n");
	}

	// Do not load SCHIP fonts to avoid garbage after FFFFFF clock
	// CHIP8 Program: "Clock Program [Bill Fisher, 1981].ch8""
	if ( !strcmp(game_signature, "F10AF20AF30AF40AF50A+27721") ) {
		quirk_ClockProgram_fonts = true;
		printf("Clock Program Quirk Enabled.\n");
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