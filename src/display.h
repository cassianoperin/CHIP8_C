#pragma once

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// ---------------------------------- Global Variables ---------------------------------- //
// Display
// unsigned char SCREEN_WIDTH = 64;

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