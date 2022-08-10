#pragma once

struct display {
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};

bool display_init(struct display* display);
bool display_draw(struct display* display, unsigned int frame);
void display_close(struct display* display);