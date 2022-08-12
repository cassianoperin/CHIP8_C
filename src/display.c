#include <SDL2/SDL.h>
#include "display.h"
#include "constant.h"

bool display_init(struct display* display)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		display->window = SDL_CreateWindow( "C_SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, SDL_WINDOW_SHOWN );
		if( display->window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			display->renderer = SDL_CreateRenderer( display->window, -1, SDL_RENDERER_ACCELERATED );
			if( display->renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				//Create texture
				display->texture = SDL_CreateTexture(display->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
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
	SDL_UpdateTexture(display->texture, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
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