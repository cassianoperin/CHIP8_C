#include <SDL2/SDL.h>
#include "display.h"

bool display_init()
{
	// Initialization flag
	bool success = true;

	// Variables
	display_SCREEN_WIDTH_X	= 64;
	display_SCREEN_HEIGHT_Y	= 32;
	display_SCALE			= 10;
	display_pixel_ON_color	= 0xFFFFFFFF;
	display_pixel_OFF_color	= 0xFF000000;
	display_color_theme		= 0;

	// Debug
	debug_pixels			= false;

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow( "CHIP8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display_SCREEN_WIDTH_X * display_SCALE, display_SCREEN_HEIGHT_Y * display_SCALE, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// --- Create renderer for window --- //
			// Display wait quirk enabled, enable vsync
			if ( quirk_display_wait ) {
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			} else {
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			}

			// Check for errors
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				// Create texture
				texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, display_SCREEN_WIDTH_X, display_SCREEN_HEIGHT_Y);
				if( renderer == NULL )
				{
					printf( "Texture could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}


bool display_draw(unsigned int frame, Scene *scene)
{
	//Initialization flag
	bool success = true;

	// Increment total frame counter
	frame ++;

	// Increment Frame Counter for FPS
	frame_counter++;

	// Update the Screen
	SDL_UpdateTexture(texture, NULL, display_pixels, display_SCREEN_WIDTH_X * sizeof(uint32_t));
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	// ----- Update Text Messages ----- //

	// Message Slot 1
	if ( string_msg1 != NULL && strcmp( string_msg1, "") != 0 ) {
		SDL_RenderCopy(renderer, scene->message1, NULL, &scene->message1_Rect);
	}
	// Message Slot 2
	if ( string_msg2 != NULL && strcmp( string_msg2, "") != 0 ) {
    	SDL_RenderCopy(renderer, scene->message2, NULL, &scene->message2_Rect);
	}
	// Message Slot 3
	if ( string_msg3 != NULL && strcmp( string_msg3, "") != 0 ) {
    	SDL_RenderCopy(renderer, scene->message3, NULL, &scene->message3_Rect);
	}
	// Message Slot 4
	// if ( string_msg4 != NULL && strcmp( string_msg4, "") != 0 ) {
	if ( string_msg4 != NULL && strcmp( string_msg4, "") != 0 ) {
    	SDL_RenderCopy(renderer, scene->message4, NULL, &scene->message4_Rect);
	}

	// Draw
	SDL_RenderPresent(renderer);

	// Draw to console
	// draw_graphics_console();

	return success;
}


void SDL_close()
{
	// Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void display_update_theme(){
	unsigned int i;

	// Update graphics vector with new colors
	for ( i = 0 ; i < 2048 ; i++ ) {
		if ( display_pixels[i] == display_pixel_ON_color ) {
			display_pixels[i] = display_pixel_ON_color_alt;
		} else {
			display_pixels[i] = display_pixel_OFF_color_alt;
		}
	}

	// Update the colors
	display_pixel_ON_color	= display_pixel_ON_color_alt;
	display_pixel_OFF_color	= display_pixel_OFF_color_alt;
}

// Print Graphics on Console
void draw_graphics_console() {

	int line, column, index = 0;

	while ( index < 2048 )
	{
		// Add an border
		printf("----------------------------------------------------------------------------------------------------------------------------------\n");

		// Lines
		for ( line = 0 ; line < 32 ; line ++ ) {

			// Add an border
			printf("|");

			// 00 ..  63
			// 64 .. 127
			// Columns
			for ( column = 0 ; column < 64 ; column ++ ) {
				if ( display_pixels[index+column] == display_pixel_ON_color ) {
					// printf("[] ");
					printf("X ");
				} else {
					// printf("   ");
					printf("  ");
				}
			}
			// Add an border
			printf("|");
			printf("\n");

			// Increment the index
			index += 64;
		}
	}

	// Add an border
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");

	// Space between screens
	printf("\n\n\n");
}