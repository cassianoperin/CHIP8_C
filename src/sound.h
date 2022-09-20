#pragma once

// ---------------------------------- Global Variables ---------------------------------- //
SDL_AudioDeviceID deviceId;
Uint8 *wavBuffer;
Uint32 wavLength;

// -------------------------------------- Functions ------------------------------------- //
void sound_init();
void sound_close();