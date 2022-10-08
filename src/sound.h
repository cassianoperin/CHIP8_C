#pragma once

#define BUFFER_DURATION 5 // Length of the buffer in seconds
#define FREQUENCY 48000 // Samples per second
#define BUFFER_LEN (BUFFER_DURATION*FREQUENCY) // Samples in the buffer

// ---------------------------------- Global Variables ---------------------------------- //
SDL_AudioDeviceID deviceId;

// -------------------------------------- Functions ------------------------------------- //
void sound_init();
void sound_close();
void play_buffer(void* userdata, unsigned char* stream, int len);
double tone(double hz, unsigned long time);
Sint16 format(double sample, double amplitude);