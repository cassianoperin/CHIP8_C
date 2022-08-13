#include <SDL2/SDL.h>
#include "cpu.h"

// Import External Variables
extern unsigned int quit;

void keyboard() {

	//Event handler
	SDL_Event event;
	
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
}