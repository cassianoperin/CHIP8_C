#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// Display
static const char SCREEN_WIDTH    = 64;
static const char SCREEN_HEIGHT   = 32;
static const char SCALE           = 10;
static const int  PIXEL_ON_COLOR   = 0xFFFFFFFF;
static const int  PIXEL_OFF_COLOR  = 0xFF000000;
unsigned int pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

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

// Screen Size
unsigned char SizeX;		// Number of Columns in Graphics
unsigned char SizeY;		// Number of Lines in Graphics
unsigned char FPS;			// Frames per second

// Filename
char* filename;
// Game signature
char *game_signature;
