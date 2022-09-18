#include <SDL2/SDL.h>
#include "display.h"


bool display_init(struct display* display)
{
	// Initialization flag
	bool success = true;

	// Variables
	display_screen_width	= 64;
	display_screen_height	= 32;
	display_scale			= 10;
	display_pixel_ON_color	= 0xFFFFFFFF;
	display_pixel_OFF_color	= 0xFF000000;

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// Create window
		display->window = SDL_CreateWindow( "C_SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display_screen_width * display_scale, display_screen_height * display_scale, SDL_WINDOW_SHOWN );
		if( display->window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// Create renderer for window
			display->renderer = SDL_CreateRenderer( display->window, -1, SDL_RENDERER_ACCELERATED );
			if( display->renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				// Create texture
				display->texture = SDL_CreateTexture(display->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, display_screen_width, display_screen_height);
				if( display->renderer == NULL )
				{
					printf( "Texture could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}


bool display_draw(struct display* display, unsigned int frame)
{
	//Initialization flag
	bool success = true;

	// Update the Screen
	SDL_UpdateTexture(display->texture, NULL, display_pixels, display_screen_width * sizeof(uint32_t));
	SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
	SDL_RenderPresent(display->renderer);
	// SDL_SetWindowTitle(display->window, "CPS:0      FPS:0");
	
	return success;
}


void display_close(struct display* display)
{
	//Destroy window	
	SDL_DestroyRenderer( display->renderer );
	SDL_DestroyWindow( display->window );
	display->window = NULL;
	display->renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}