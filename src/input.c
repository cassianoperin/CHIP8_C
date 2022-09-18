#include <SDL2/SDL.h>
#include "input.h"
#include "cpu.h"


void input_keyboard() {



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
					Key[0x1] = 1;
					break;

				case SDLK_2:
					Key[0x2] = 1;
					break;

				case SDLK_3:
					Key[0x3] = 1;
					break;

				case SDLK_4:
					Key[0xC] = 1;
					break;

				case SDLK_q:
					Key[0x4] = 1;
					break;

				case SDLK_w:
					Key[0x5] = 1;
					break;

				case SDLK_e:
					Key[0x6] = 1;
					break;

				case SDLK_r:
					Key[0xD] = 1;
					break;

				case SDLK_a:
					Key[0x7] = 1;
					break;

				case SDLK_s:
					Key[0x8] = 1;
					break;

				case SDLK_d:
					Key[0x9] = 1;
					break;

				case SDLK_f:
					Key[0xE] = 1;
					break;

				case SDLK_z:
					Key[0xA] = 1;
					break;

				case SDLK_x:
					Key[0x0] = 1;
					break;

				case SDLK_c:
					Key[0xB] = 1;
					break;

				case SDLK_v:
					Key[0xF] = 1;
					break;

				// Interface

				// Pause
				case SDLK_p:
					cpu_pause = !cpu_pause;
					break;

				// Change Theme
				case SDLK_6: {

					// Jump to next color theme
					if ( display_color_theme < 5 ) {
						display_color_theme ++;
					} else {
						display_color_theme = 0;
					}
					
					//Select surfaces based on key press
					switch( display_color_theme )
					{
						// Black and White
						case 0:
							display_pixel_ON_color_alt	= 0xFFFFFFFF;
							display_pixel_OFF_color_alt	= 0xFF000000;

							display_update_theme();
							break;

						// White and Black
						case 1: {
							// New colors
							display_pixel_ON_color_alt	= 0xFF000000;
							display_pixel_OFF_color_alt	= 0xFFFFFFFF;

							display_update_theme();
							break;
						}

						// Grey Wolfand and Crystal Blue
						case 2: {
							// New colors
							display_pixel_ON_color_alt	= 0xFF5CB3FF;
							display_pixel_OFF_color_alt	= 0xFF504A4B;

							display_update_theme();
							break;
						}

						// Cloudy Gray and Emerald Green
						case 3: {
							// New colors
							display_pixel_ON_color_alt	= 0xFF50C878;
							display_pixel_OFF_color_alt	= 0xFF6D6968;

							display_update_theme();
							break;
						}

						// Night Black and Pastel Yellow
						case 4: {
							// New colors
							display_pixel_ON_color_alt	= 0xFFFAF884;
							display_pixel_OFF_color_alt	= 0xFF0C090A;

							display_update_theme();
							break;
						}


						// LightCoral Pink and Salmon
						case 5: {
							// New colors
							display_pixel_ON_color_alt	= 0xFFF08080;
							display_pixel_OFF_color_alt	= 0xFF3A3B3C;

							display_update_theme();
							break;
						}
					}
					break;
				}

				// Debug
				case SDLK_9:
					cpu_debug_mode = !cpu_debug_mode;
					// cpu_debug_mode = false;
					break;

				// Reset
				case SDLK_0:
					cpu_reset();
					break;

				case SDLK_ESCAPE:
					quit = true;
					break;
			}

		} else if (event.type == SDL_KEYUP) {
			
			//Select surfaces based on key press
			switch( event.key.keysym.sym )
			{
				case SDLK_1:
					Key[0x1] = 0;
					break;

				case SDLK_2:
					Key[0x2] = 0;
					break;

				case SDLK_3:
					Key[0x3] = 0;
					break;

				case SDLK_4:
					Key[0xC] = 0;
					break;

				case SDLK_q:
					Key[0x4] = 0;
					break;

				case SDLK_w:
					Key[0x5] = 0;
					break;

				case SDLK_e:
					Key[0x6] = 0;
					break;

				case SDLK_r:
					Key[0xD] = 0;
					break;

				case SDLK_a:
					Key[0x7] = 0;
					break;

				case SDLK_s:
					Key[0x8] = 0;
					break;

				case SDLK_d:
					Key[0x9] = 0;
					break;

				case SDLK_f:
					Key[0xE] = 0;
					break;

				case SDLK_z:
					Key[0xA] = 0;
					break;

				case SDLK_x:
					Key[0x0] = 0;
					break;

				case SDLK_c:
					Key[0xB] = 0;
					break;

				case SDLK_v:
					Key[0xF] = 0;
					break;
			}

		} else if (event.type == SDL_QUIT)
		{
			quit = true;
		}
	}
}