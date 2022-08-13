#include <SDL2/SDL.h>
#include "lib.h"
#include "display.h"
#include "cpu.h"

// Global Variables
unsigned int Cycle = 0;
unsigned int CycleCounter = 0;
unsigned int CycleCounterCPU = 0;
unsigned int Frame = 0;
unsigned int FrameCounter = 0;
unsigned int lastTime_second = 0;
unsigned int lastTime_fps = 0;
unsigned int lastTime_cpu = 0;
unsigned int currentTime = 0;

// extern bool SCHIP_TimerHack;

// -------------------------------- main -------------------------------- //

int main( int argc, char* args[] )
{
	// Variables
	struct display display;
	char* filename = (char*)"/Users/cassiano/go/src/C_SDL/src/pong.ch8";
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

				// Update timer variables
				lastTime_cpu = currentTime;

				// // Reset counters
				CycleCounterCPU ++;
			}

			// ------------------------------ Ticker FPS ------------------------------ //

			// Ticker FPS (60 times per second)
			if ( ticker_fps(lastTime_fps, currentTime) ) {

				// Handle events on queue
				while( SDL_PollEvent( &event ) != 0 )
				{
					if (event.type == SDL_KEYDOWN)
					{
						//Select surfaces based on key press
                        switch( event.key.keysym.sym )
                        {
							case SDLK_1:
								printf("KEY 1\n");
								Key[0x1] = 1;
								break;

							case SDLK_2:
								printf("KEY 2\n");
								Key[0x2] = 1;
								break;

							case SDLK_3:
								printf("KEY 3\n");
								Key[0x3] = 1;
								break;

							case SDLK_4:
								printf("KEY C\n");
								Key[0xC] = 1;
								break;

							case SDLK_q:
								printf("KEY 4\n");
								Key[0x4] = 1;
								break;

							case SDLK_w:
								printf("KEY 5\n");
								Key[0x5] = 1;
								break;

							case SDLK_e:
								printf("KEY 6\n");
								Key[0x6] = 1;
								break;

							case SDLK_r:
								printf("KEY D\n");
								Key[0xD] = 1;
								break;

							case SDLK_a:
								printf("KEY 7\n");
								Key[0x7] = 1;
								break;

							case SDLK_s:
								printf("KEY 8\n");
								Key[0x8] = 1;
								break;

							case SDLK_d:
								printf("KEY 9\n");
								Key[0x9] = 1;
								break;

							case SDLK_f:
								printf("KEY E\n");
								Key[0xE] = 1;
								break;

							case SDLK_z:
								printf("KEY A\n");
								Key[0xA] = 1;
								break;

							case SDLK_x:
								printf("KEY 0\n");
								Key[0x0] = 1;
								break;

							case SDLK_c:
								printf("KEY B\n");
								Key[0xB] = 1;
								break;

							case SDLK_v:
								printf("KEY F\n");
								Key[0xF] = 1;
								break;

							// Interface

							case SDLK_p:
								printf("KEY P\n");
								Pause = !Pause;
								break;

							case SDLK_ESCAPE:
								printf("KEY ESC\n");
								quit = true;
								break;
                        }

					} else if (event.type == SDL_KEYUP) {
						
						//Select surfaces based on key press
                        switch( event.key.keysym.sym )
                        {
							case SDLK_1:
								printf("KEY 1\n");
								Key[0x1] = 0;
								break;

							case SDLK_2:
								printf("KEY 2\n");
								Key[0x2] = 0;
								break;

							case SDLK_3:
								printf("KEY 3\n");
								Key[0x3] = 0;
								break;

							case SDLK_4:
								printf("KEY C\n");
								Key[0xC] = 0;
								break;

							case SDLK_q:
								printf("KEY 4\n");
								Key[0x4] = 0;
								break;

							case SDLK_w:
								printf("KEY 5\n");
								Key[0x5] = 0;
								break;

							case SDLK_e:
								printf("KEY 6\n");
								Key[0x6] = 0;
								break;

							case SDLK_r:
								printf("KEY D\n");
								Key[0xD] = 0;
								break;

							case SDLK_a:
								printf("KEY 7\n");
								Key[0x7] = 0;
								break;

							case SDLK_s:
								printf("KEY 8\n");
								Key[0x8] = 0;
								break;

							case SDLK_d:
								printf("KEY 9\n");
								Key[0x9] = 0;
								break;

							case SDLK_f:
								printf("KEY E\n");
								Key[0xE] = 0;
								break;

							case SDLK_z:
								printf("KEY A\n");
								Key[0xA] = 0;
								break;

							case SDLK_x:
								printf("KEY 0\n");
								Key[0x0] = 0;
								break;

							case SDLK_c:
								printf("KEY B\n");
								Key[0xB] = 0;
								break;

							case SDLK_v:
								printf("KEY F\n");
								Key[0xF] = 0;
								break;
                        }

					} else if (event.type == SDL_QUIT)
					{
						quit = true;
					}
				}


				// Delay Timer
				// When ticker run (60 times in a second, check de DelayTimer)
				// SCHIP Uses a hack to decrease DT faster to gain speed
				// if ( !SCHIP_TimerHack ) {
				// 	if ( DelayTimer > 0 ) {
				// 		DelayTimer--;
				// 	}
				// }

				// Draw screen
				display_draw(&display, FrameCounter);

				// Update timer variables
				lastTime_fps = currentTime;

				// Increment total frame counter
				Frame ++;
				// Increment frame counter for FPS
				FrameCounter++;
			}

			// ---------------------------- Ticker Second ---------------------------- //

			if ( ticker_second(lastTime_second, currentTime) ) {

				// Cycles and FPS Measurement
				char title_msg[510];
				sprintf(title_msg, "CPS: %d\tFPS: %d\tCPU: %d", CycleCounter, FrameCounter+1, CycleCounterCPU);
				SDL_SetWindowTitle(display.window, title_msg);

				// Update timer variables
				lastTime_second = currentTime;

				// Reset counters
				CycleCounter = 0;
				FrameCounter = 0;
				CycleCounterCPU = 0;
			}

			// ----------------------------- Interpreter ----------------------------- //




			// Increment CPU Cycle
			Cycle++;
			// Increment Cycle counter for FPS
			CycleCounter++;

			// printf("\n\n\n\n%02X\n\n\n", DelayTimer);
			if ( DelayTimer > 0 ) {
					DelayTimer--;
			}

			if ( SoundTimer > 0 ) {
					SoundTimer--;
			}

			// Kill on first cycle for tests
			// break;
		}
	}

	//Free resources and close SDL
	display_close(&display);

	return 0;
}