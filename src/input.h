#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// -------------------------- External Variables and functions -------------------------- //
extern bool          quit;
extern unsigned int  display_pixel_ON_color;
extern unsigned int  display_pixel_OFF_color;
extern unsigned int  display_pixel_ON_color_alt;
extern unsigned int  display_pixel_OFF_color_alt;
extern unsigned int  display_pixels[2048]; 
extern unsigned char display_color_theme;
extern char   *lib_game_signature;
extern unsigned char   Key[];
extern bool cpu_pause;
extern bool cpu_debug_mode;
// External Functions
extern void display_update_theme();
extern void cpu_reset();

// ---------------------------------- Global Variables ---------------------------------- //
bool input_remap_flag;
unsigned char input_remap_btn_UP;
unsigned char input_remap_btn_DOWN;
unsigned char input_remap_btn_LEFT;
unsigned char input_remap_btn_RIGHT;
unsigned char input_remap_btn_SPACE;

// -------------------------------------- Functions ------------------------------------- //
void input_keyboard();
void input_keyboard_remaps();