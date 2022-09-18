#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// ---------------------------------- Global Variables ---------------------------------- //
// Display
unsigned char display_screen_width;
unsigned char display_screen_height;
unsigned char display_scale;
unsigned int  display_pixel_ON_color;
unsigned int  display_pixel_OFF_color;
// unsigned int pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
unsigned int  display_pixels[2048];
// Screen Size
unsigned char display_sizeX;		// Number of Columns in Graphics
unsigned char display_sizeY;		// Number of Lines in Graphics
unsigned char display_FPS;			// Frames per second

// ---------------------------------- Global Variables ---------------------------------- //
struct display {
  SDL_Window*   window;
  SDL_Renderer* renderer;
  SDL_Texture*  texture;
};

// -------------------------------------- Functions ------------------------------------- //
bool display_init(struct display* display);
bool display_draw(struct display* display, unsigned int frame);
void display_close(struct display* display);