#pragma once
#include "typedef.h"

#define Max_Overclock 5000

// --------------------------------- External Variables --------------------------------- //
// Main
extern bool          quit;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern unsigned int cycle_counter;
extern unsigned int message_slot4_timer;
extern const int pal_freq;
// Display
extern unsigned int  display_pixel_ON_color;
extern unsigned int  display_pixel_OFF_color;
extern unsigned int  display_pixel_ON_color_alt;
extern unsigned int  display_pixel_OFF_color_alt;
extern unsigned int  display_pixels[2048]; 
extern unsigned char display_color_theme;
extern unsigned int  frame_counter;
extern Scene scene;
// Lib
extern char *game_signature;
// CPU
extern unsigned char   Key[];
extern bool cpu_pause;
extern bool cpu_debug_mode;
// extern unsigned int    cycle_counter_cpu;
extern unsigned int CPU_CLOCK;
// Font
extern char *string_msg1, *string_msg2, *string_msg3, *string_msg4;
extern bool msg_emuinfo;
// Sound
extern bool sound_enabled;

// --------------------------------- External Functions --------------------------------- //
// CPU
extern void cpu_reset();
// Display
extern void display_update_theme();
extern bool display_draw(unsigned int frame, Scene *scene);
// Font
extern void font_update_msg1(SDL_Renderer *renderer);
extern void font_update_msg2(SDL_Renderer *renderer);
extern void font_update_msg3(SDL_Renderer *renderer);
extern void font_update_msg4(SDL_Renderer *renderer);

// ---------------------------------- Global Variables ---------------------------------- //
bool            input_remap_flag;
unsigned char   input_remap_btn_UP;
unsigned char   input_remap_btn_DOWN;
unsigned char   input_remap_btn_LEFT;
unsigned char   input_remap_btn_RIGHT;
unsigned char   input_remap_btn_SPACE;

// -------------------------------------- Functions ------------------------------------- //
void input_keyboard();
void input_keyboard_remaps();