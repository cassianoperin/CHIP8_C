#include <SDL2/SDL.h>
#include "lib.h"
#include "display.h"
#include "cpu.h"

// Global Variables
unsigned int Cycle = 0;
unsigned int CycleCounter = 0;
unsigned int Frame = 0;
unsigned int FrameCounter = 0;
unsigned int lastTime_second = 0;
unsigned int lastTime_fps = 0;
unsigned int currentTime = 0;

// -------------------------------- main -------------------------------- //

int main( int argc, char* args[] )
{
	// Variables
	struct display display;
	char* filename = (char*)"/Users/cassiano/go/src/C_SDL/src/rush.ch8";
	// char* filename = args[1];

	// Initialize
	Initialize();

	// Load ROM into Memory
	load_rom(filename,  Memory, sizeof(Memory));

	//Start up SDL and create window
	if( !display_init(&display) )
	{
		printf( "Failed to initialize SDL!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event event;

		// ----------------------- Infinite Loop  ----------------------- //
		while( !quit )
		{
			// Current time
			currentTime = SDL_GetTicks();


			// Ticker Second
			if ( ticker_second(lastTime_second, currentTime) ) {

				// Cycles and FPS Measurement
				char title_msg[30];
				sprintf(title_msg, "CPS: %d\t\tFPS: %d", CycleCounter, FrameCounter+1);
				SDL_SetWindowTitle(display.window, title_msg);

				// Update timer variables
				lastTime_second = currentTime;

				// Reset counters
				CycleCounter = 0;
				FrameCounter = 0;
			}

			// Ticker FPS (60 times per second)
			if ( ticker_fps(lastTime_fps, currentTime) ) {

				// Handle events on queue
				while( SDL_PollEvent( &event ) != 0 )
				{
					if (event.type == SDL_KEYDOWN)
					{
						const char* key = SDL_GetKeyName(event.key.keysym.sym);
						if (strcmp(key,"Q") == 0 || strcmp(key,"Escape") == 0)
						{
							quit = true;
						}
					}
					else if (event.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				// Draw screen
				display_draw(&display, FrameCounter);

				// Update timer variables
				lastTime_fps = currentTime;

				// Increment total frame counter
				Frame ++;
				// Increment frame counter for FPS
				FrameCounter++;
			}

			Interpreter();

			// Increment CPU Cycle
			Cycle++;
			// Increment Cycle counter for FPS
			CycleCounter++;

			// Kill on first cycle for tests
			// break;
		}
	}

	//Free resources and close SDL
	display_close(&display);

	return 0;
}