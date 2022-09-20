#include <SDL2/SDL.h>
#include "sound.h"

void sound_init()
{
	// Initialize SDL_Audio
	if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL Audio could not initialize! SDL Error: %s\n", SDL_GetError() );
		exit(2);
	}
	else
	{
		// Variables
		char* sound_file = "beep.wav";

		// load WAV file
		SDL_AudioSpec wavSpec;
		// Uint32 wavLength;	// Moved to global
		// Uint8 *wavBuffer;	// Moved to global
		if( SDL_LoadWAV(sound_file, &wavSpec, &wavBuffer, &wavLength) == NULL) {
			printf("Unable to load sound file: %s\nExiting.\n", sound_file);
			exit(2);
		}

		// open audio device
		// SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
		deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

		// // play audio
		// int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
		// if ( success != 0 ) {
		// 	printf("Unable to PLAY sound file: %s\nExiting.\n", sound_file);
		// }

		// SDL_PauseAudioDevice(deviceId, 0);
		// SDL_Delay(1000);
		// SDL_PauseAudioDevice(deviceId, 1);

		// // clean up
		// SDL_CloseAudioDevice(deviceId);
		// SDL_FreeWAV(wavBuffer);
		// SDL_Quit();
	}
}


void sound_close()
{
	// Destroy Audio
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}