#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// LIB
extern char *lib_game_signature;
extern char *string_msg4;
// CPU
extern unsigned char	Memory[4096];
extern bool             cpu_halt;
extern bool             cpu_draw_flag;
extern bool             cpu_original_draw_mode;
extern unsigned char	DelayTimer;
extern unsigned char	SoundTimer;
extern bool             cpu_pause;
extern unsigned int     cycle_counter_cpu;
// Display
extern Scene            scene;
extern unsigned int     frame;
extern unsigned int     frame_counter;
// Audio
SDL_AudioDeviceID       audio_device_id;

// --------------------------------- External Functions --------------------------------- //
// Font
extern bool font_init(SDL_Renderer* renderer);
extern void font_update_msg1(SDL_Renderer* renderer);
extern void font_update_msg2(SDL_Renderer* renderer);
extern void font_update_msg3(SDL_Renderer* renderer);
extern void font_update_msg4(SDL_Renderer* renderer);
// CLI
extern void command_line_interface(int argc, char* args[]);
// LIB
extern bool ticker_second(unsigned int lastTime, unsigned int currentTime);
extern bool ticker_fps(unsigned int lastTime, unsigned int currentTime);
extern bool ticker_cpu(unsigned int lastTime, unsigned int currentTime);
extern void showCPS(long long unsigned int number);
extern void showFPS(int number);
extern void showCPU_CPS(int number);
extern void load_rom(char* filename, unsigned char *mem, unsigned int mem_size);
extern void get_game_signature(char* filename, char **s);
// CPU
extern void cpu_initialize();
extern void cpu_load_fonts();
extern void cpu_interpreter();
extern unsigned int CPU_CLOCK;
// QUIRKS
extern void handle_legacy_opcodes();
// Input
extern void input_keyboard();
extern void input_keyboard_remaps();
// Display
extern bool display_init();
extern bool display_draw(unsigned int frame, Scene *scene);
extern void SDL_close();
// Audio
extern void sound_init();
extern void sound_close();


// ---------------------------------- Global Variables ---------------------------------- //
// SDL Video
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

int FONTX = 0;

// // SDL Font
TTF_Font *font;
SDL_Surface *text;

// Game path and ROM name
char* filename;

// Control the Main loop exit
bool quit;

// Cycle Counters
unsigned int cycle = 0;             // Main loop cycles
unsigned int cycle_counter = 0;     // Main loop cyles/second

