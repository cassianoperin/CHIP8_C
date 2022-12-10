#pragma once

#define BUFFER_DURATION 1 // Length of the buffer in seconds
#define FREQUENCY 48000 // Samples per second
#define BUFFER_LEN (BUFFER_DURATION*FREQUENCY) // Samples in the buffer

// ---------------------------------- Global Variables ---------------------------------- //
SDL_AudioDeviceID audio_device_id;
uint64_t samples_played;

// -------------------------------------- Functions ------------------------------------- //
void sound_init();
void sound_close();
void audio_callback(void* userdata, uint8_t* stream, int len);