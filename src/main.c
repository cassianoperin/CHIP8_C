#include <SDL2/SDL.h>
#include <string.h>
#include "lib.h"
#include "display.h"
#include "cli.h"
#include "cpu.h"
#include "input.h"
#include "quirks.h"


// --------------------------------- External Variables --------------------------------- //
extern char *game_signature;


// ---------------------------------- Global Variables ---------------------------------- //
unsigned int cycle		= 0;		// Main loop cycles
unsigned int cycle_cpu	= 0;		// Executed cpu cycles
bool quit				= false;	// Main loop flag
char* filename;						// game path and file name


// ------------------------------------ Main Program ------------------------------------ //

int main( int argc, char* args[] )
{
	// Counters
	unsigned int cycle_counter				= 0;
	unsigned int cycle_counter_cpu			= 0;
	unsigned int frame						= 0;
	unsigned int frame_counter				= 0;
	// Tickers
	unsigned int tickers_current_time		= 0;
	unsigned int ticker_second_last_time	= 0;
	unsigned int ticker_fps_last_time 		= 0;
	unsigned int ticker_cpu_last_time		= 0;
	struct display display;

	// Initialize
	cpu_initialize();

	// CLI
	// command_line_interface(argc, args);

	// File name
	// char* filename = args[1];
	// char* filename = (char*)"/Users/cassiano/go/src/CHIP8_C/#Games/# Not Supported Platforms/Chip-8X and Hybrids/ETI660 Hybrids/Pong (ETI660 Hybrid).ch8";
	// char* filename = (char*)"/Users/cassiano/go/src/CHIP8_C/#Games/SuperChip/Demos/Robot.ch8";
	//
	// char* filename = "/Users/cassiano/go/src/CHIP8_C/#Games/Chip-8/Games/Breakout (Brix hack) [David Winter, 1997].ch8";
	// char* filename = (char*)"/Users/cassiano/go/src/CHIP8_C/#Games/Chip-8/Programs/Clock Program [Bill Fisher, 1981].ch8";
	// char* filename = (char*)"/Users/cassiano/go/src/CHIP8_C/#Games/Chip-8/Test_Programs/chip8-test-suite.ch8";
	filename = "/Users/cassiano/go/src/CHIP8_C/#Games/Chip-8/Games/Breakout (Brix hack) [David Winter, 1997].ch8";

	// Load ROM into Memory
	load_rom(filename,  Memory, sizeof(Memory));
	printf("Loaded game: %s\n", filename);

	// Get Game signature for Qwirks
	get_game_signature(filename, &game_signature);
	printf("Signature:   %s\n", game_signature);

	// Check for Quirks
	handle_legacy_opcodes(game_signature);

	// Load Fonts
	cpu_load_fonts();

	//Start up SDL and create window
	if( !display_init(&display) )
	{
		printf( "Failed to initialize SDL!\n" );
	}
	else
	{

		// ------------------------------ Infinite Loop  ------------------------------ //
		while( !quit )
		{
			// Current time
			tickers_current_time = SDL_GetTicks();

			// ------------------------------ Ticker CPU ------------------------------ //

			if ( ticker_cpu(ticker_cpu_last_time, tickers_current_time) ) {

				if ( !cpu_pause ) {
					cpu_interpreter();
				}

				// 
				if ( cpu_original_draw_mode ) {
					if ( cpu_draw_flag ) {
						display_draw(&display, frame_counter);

						// Increment total frame counter
						frame ++;
						// Increment frame counter for FPS
						frame_counter++;
					}
				}

				// Update timer variables
				ticker_cpu_last_time = tickers_current_time;

				// Increment CPU Cycles
				cycle_cpu ++;

				// // Reset counters
				cycle_counter_cpu ++;
			}

			// ------------------------------ Ticker FPS ------------------------------ //

			// Ticker FPS (60 times per second)
			if ( ticker_fps(ticker_fps_last_time, tickers_current_time) ) {

				// Handle Keyboard
				input_keyboard();

				// Handle Delay Timer
				if ( DelayTimer > 0 ) {
					DelayTimer--;
				}

				// Handle Sound Timer
				if ( SoundTimer > 0 ) {
						SoundTimer--;
				}

				// Draw screen
				if ( !cpu_original_draw_mode ) {
					display_draw(&display, frame_counter);

					// Increment total frame counter
					frame ++;
					// Increment frame counter for FPS
					frame_counter++;
				}

				// Update timer variables
				ticker_fps_last_time = tickers_current_time;
			}

			// ---------------------------- Ticker Second ---------------------------- //

			if ( ticker_second(ticker_second_last_time, tickers_current_time) ) {

				// Cycles and FPS Measurement
				char title_msg[510];
				sprintf(title_msg, "CPS: %d\t\tFPS: %d\t\tCPU: %d", cycle_counter, frame_counter+1, cycle_counter_cpu);
				SDL_SetWindowTitle(display.window, title_msg);

				// Update timer variables
				ticker_second_last_time = tickers_current_time;

				// Reset counters
				cycle_counter = 0;
				frame_counter = 0;
				cycle_counter_cpu = 0;
			}

			// Increment main loop cycle counter
			cycle++;

			// Increment Cycle per second counter
			cycle_counter++;
		}
	}

	//Free resources and close SDL
	display_close(&display);

	return 0;
}