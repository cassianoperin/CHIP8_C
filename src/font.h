#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// SDL Font
extern TTF_Font *font;
extern SDL_Surface *text;
extern Scene scene;
extern unsigned char display_SCREEN_WIDTH_X;
extern unsigned char display_SCREEN_HEIGHT_Y;
extern unsigned char display_SCALE;

// ---------------------------------- Global Variables ---------------------------------- //
SDL_Color font_foreground_color;
SDL_Color font_background_color;
TextRenderMethod rendermethod;
RenderType rendertype;
int ptsize;
int renderstyle;
int outline;
int hinting;
int kerning;
char *string_msg1, *string_msg2, *string_msg3, *string_msg4, *font_path;
bool msg_emuinfo;

// -------------------------------------- Constants ------------------------------------- //
const char Chip8Fontset[80] = { \
	0xF0, 0x90, 0x90, 0x90, 0xF0,// 0
	0x20, 0x60, 0x20, 0x20, 0x70,// 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0,// 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0,// 3
	0x90, 0x90, 0xF0, 0x10, 0x10,// 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0,// 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0,// 6
	0xF0, 0x10, 0x20, 0x40, 0x40,// 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0,// 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0,// 9
	0xF0, 0x90, 0xF0, 0x90, 0x90,// A
	0xE0, 0x90, 0xE0, 0x90, 0xE0,// B
	0xF0, 0x80, 0x80, 0x80, 0xF0,// C
	0xE0, 0x90, 0x90, 0x90, 0xE0,// D
	0xF0, 0x80, 0xF0, 0x80, 0xF0,// E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
}; // 8 columns (bits) per 5 lines sprites


const char SCHIPFontset[160] = {  \
	0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, // 0
	0x18, 0x78, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0xff, // 1
	0xff, 0xff, 0x03, 0x03, 0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, // 2
	0xff, 0xff, 0x03, 0x03, 0xff, 0xff, 0x03, 0x03, 0xff, 0xff, // 3
	0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, // 4
	0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, 0x03, 0x03, 0xff, 0xff, // 5
	0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, // 6
	0xff, 0xff, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x18, 0x18, 0x18, // 7
	0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, // 8
	0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, 0x03, 0x03, 0xff, 0xff, // 9
	0x7e, 0xff, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3, 0xc3, // A
	0xfc, 0xfc, 0xc3, 0xc3, 0xfc, 0xfc, 0xc3, 0xc3, 0xfc, 0xfc, // B
	0x3c, 0xff, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xff, 0x3c, // C
	0xfc, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xfc, // D
	0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, // E
	0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0  // F
}; // 8 columns (bits) per 10 lines sprites

// -------------------------------------- Functions ------------------------------------- //
bool font_init(SDL_Renderer *renderer);
void font_update_msg1(SDL_Renderer *renderer);
void font_update_msg2(SDL_Renderer *renderer);
void font_update_msg3(SDL_Renderer *renderer);