#pragma once
#include "typedef.h"

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// --------------------------------- External Variables --------------------------------- //
// SDL Video
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
// SDL Font
extern char *string_msg1, *string_msg2;

// ---------------------------------- Global Variables ---------------------------------- //
// Display (Screen size)
Scene scene;
unsigned char display_SCREEN_WIDTH_X;
unsigned char display_SCREEN_HEIGHT_Y;
unsigned char display_SCALE;
unsigned int  display_pixel_ON_color;
unsigned int  display_pixel_OFF_color;
// Color Themes
unsigned char display_color_theme;          // Theme number
unsigned int  display_pixel_ON_color_alt;   // New color of enabled pixels
unsigned int  display_pixel_OFF_color_alt;  // New color of disabled pixels

// Display Array
unsigned int  display_pixels[2048];
// Frames per second
unsigned char display_FPS;

// -------------------------------------- Functions ------------------------------------- //
bool display_init();
bool display_draw(unsigned int frame, Scene *scene);
void SDL_close();
void display_update_theme();