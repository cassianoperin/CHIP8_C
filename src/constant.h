#pragma once

// Display
static const char SCREEN_WIDTH    = 64;
static const char SCREEN_HEIGHT   = 32;
static const char SCALE           = 10;
static const int  PIXEL_ON_COLOR   = 0xFFFFFFFF;
static const int  PIXEL_OFF_COLOR  = 0xFF000000;
uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];