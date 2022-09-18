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
//
extern void display_update_theme();

// -------------------------------------- Functions ------------------------------------- //
void input_keyboard();