#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// Audio
extern SDL_AudioDeviceID deviceId;
extern Uint8 *wavBuffer;


// ---------------------------------- Global Variables ---------------------------------- //
// Display (Screen size)
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
// unsigned int pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
// Frames per second
unsigned char display_FPS;			

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
void display_update_theme();