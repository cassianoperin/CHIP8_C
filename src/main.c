#include <SDL2/SDL.h>
#include "lib.h"
#include "display.h"
#include "cpu.h"
#include "input.h"
#include "qwirks.h"


// Global Variables
unsigned int Cycle = 0;		// Main loop cycles
bool quit = false;			//Main loop flag

// -------------------------------- main -------------------------------- //

int main( int argc, char* args[] )
{
	// Variables
	unsigned int CycleCounter = 0;
	unsigned int CycleCounterCPU = 0;
	unsigned int Frame = 0;
	unsigned int FrameCounter = 0;
	unsigned int lastTime_second = 0;
	unsigned int lastTime_fps = 0;
	unsigned int lastTime_cpu = 0;
	unsigned int currentTime = 0;
	char *game_signature = "";
	struct display display;
	// char* filename = (char*)"/Users/cassiano/go/src/C_SDL/src/pong.ch8";
	char* filename = (char*)"/Users/cassiano/go/src/CHIP8_C/#Games/Chip-8/Test_Programs/c8_test.c8";

	// Initialize
	Initialize();

	// Load ROM into Memory
	load_rom(filename,  Memory, sizeof(Memory));
	printf("Loaded game: %s\n", filename);

	// Get Game signature for Qwirks
	get_game_signature(filename, &game_signature);
	printf("Signature:   %s\n", game_signature);

	// Check for Quirks
	Handle_legacy_opcodes(game_signature);

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
			currentTime = SDL_GetTicks();

			// ------------------------------ Ticker CPU ------------------------------ //

			if ( ticker_cpu(lastTime_cpu, currentTime) ) {

				if ( !Pause ) {
					Interpreter();
				}

				// Handle Delay Timer
				if ( DelayTimer > 0 ) {
					DelayTimer--;
				}

				// Handle Sound Timer
				if ( SoundTimer > 0 ) {
						SoundTimer--;
				}

				// 
				if ( OriginalDrawMode ) {
					if ( drawFlag ) {
						display_draw(&display, FrameCounter);

						// Increment total frame counter
						Frame ++;
						// Increment frame counter for FPS
						FrameCounter++;
					}
				}

				// Update timer variables
				lastTime_cpu = currentTime;

				// // Reset counters
				CycleCounterCPU ++;
			}

			// ------------------------------ Ticker FPS ------------------------------ //

			// Ticker FPS (60 times per second)
			if ( ticker_fps(lastTime_fps, currentTime) ) {

				// Handle Keyboard
				keyboard();

				// Draw screen
				if ( !OriginalDrawMode ) {
					display_draw(&display, FrameCounter);

					// Increment total frame counter
					Frame ++;
					// Increment frame counter for FPS
					FrameCounter++;
				}

				// Update timer variables
				lastTime_fps = currentTime;
			}

			// ---------------------------- Ticker Second ---------------------------- //

			if ( ticker_second(lastTime_second, currentTime) ) {

				// Cycles and FPS Measurement
				char title_msg[510];
				sprintf(title_msg, "CPS: %d\t\tFPS: %d\t\tCPU: %d", CycleCounter, FrameCounter+1, CycleCounterCPU);
				SDL_SetWindowTitle(display.window, title_msg);

				// Update timer variables
				lastTime_second = currentTime;

				// Reset counters
				CycleCounter = 0;
				FrameCounter = 0;
				CycleCounterCPU = 0;
			}

			// Increment CPU Cycle
			Cycle++;

			// Increment Cycle per second counter
			CycleCounter++;
		}
	}

	//Free resources and close SDL
	display_close(&display);

	return 0;
}