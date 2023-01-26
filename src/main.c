#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "main.h"
// #include <unistd.h>

int main( int argc, char* args[] )
{
	// Sound
	bool playing_sound						= false;
	// Tickers
	unsigned int tickers_current_time		= 0;
	unsigned int ticker_second_last_time	= 0;
	unsigned int ticker_fps_last_time 		= 0;
	unsigned int ticker_cpu_last_time		= 0;
	// Main loop control
	quit								= false;

	// Initialize
	cpu_initialize();



	// CLI
	// command_line_interface(argc, args);

	// File name
	// char* filename = args[1];
	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/# Not Supported Platforms/Chip-8X and Hybrids/ETI660 Hybrids/Pong (ETI660 Hybrid).ch8";
	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/SuperChip/Demos/Robot.ch8";
	//
	// char* filename = "/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Games/Breakout (Brix hack) [David Winter, 1997].ch8";
	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Programs/Clock Program [Bill Fisher, 1981].ch8";

	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Test_Programs/chip8-test-suite.ch8";
	// filename = "/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Games/Breakout (Brix hack) [David Winter, 1997].ch8";

	// filename = "/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Games/Tank.ch8";
	filename = "/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Games/Pong (1 player).ch8";

	// Load ROM into Memory
	load_rom(filename,  Memory,  (sizeof(Memory) / sizeof(Memory[0])) );
	printf("Loaded game: %s\n", filename);

	// Get Game signature for Qwirks
	game_signature = get_game_signature(filename);
	printf("Signature:   %s\n", game_signature );

	// Check for Quirks
	handle_legacy_opcodes(game_signature);

	// Free TESTTTTT!!!!!

	// Load Fonts
	cpu_load_fonts();

	// Keyboard remaps
	input_keyboard_remaps();

	// Initialize Audio System
	sound_init();

	// ------------------------------ Font Init ------------------------------ //
	font_init(renderer);

	//Start up SDL and create window
	if( !display_init() )
	{
		printf( "Failed to initialize SDL!\n" );
	}
	else
	{
		// ------------------------------ Infinite Loop  ------------------------------ //
		while( !quit )
		{


			// Future avoid of unnecessary loop cycles
			// Maybe calculate the time per cycle and wait?
			// SDL_Delay(1);
			// usleep(500);

			// Increment main loop cycle counter
			cycle++;

			// Increment Cycle per second counter
			cycle_counter++;

			// Current time
			tickers_current_time = SDL_GetTicks();

			// ---------------------------- Ticker Second ---------------------------- //

			if ( ticker_second(ticker_second_last_time, tickers_current_time) ) {

				// At least one draw per second
				display_draw(frame_counter, &scene);

				if ( msg_emuinfo ) {
					// -------- Message slot 1 -------- //
					showCPS(cycle_counter);
					font_update_msg1(renderer);

					// -------- Message slot 2 -------- //
					showCPU_CPS(cycle_counter_cpu);
					font_update_msg2(renderer);

					// -------- Message slot 3 -------- //
					showFPS(frame_counter);
					font_update_msg3(renderer);
				} else {
					// Clean messages
					string_msg1 = "";
					string_msg2 = "";
					string_msg3 = "";
				}

				// Message slot 4 timer
				if ( message_slot4_timer > 0 ) {
					message_slot4_timer --;

					// When reach zero, clear
					if ( message_slot4_timer == 0 ) {
						string_msg4 = "";
					}
				}

				// Update timer variables
				ticker_second_last_time = tickers_current_time;

				// Cycles and FPS Measurement
				// char title_msg[510];
				// sprintf(title_msg, "CPS: %d\t\tFPS: %d\t\tCPU: %d", cycle_counter, frame_counter, cycle_counter_cpu);
				// SDL_SetWindowTitle(window, title_msg);

				// Reset counters
				cycle_counter = 0;
				frame_counter = 0;
				cycle_counter_cpu = 0;
			}


			// ------------------------------ Ticker CPU ------------------------------ //

			if ( ticker_cpu(ticker_cpu_last_time, tickers_current_time) ) {

				if ( !cpu_pause ) {

					if (!cpu_halt) {
						// Ensure that CPU will run exactly the defined clock
						// Sometimes the milliseconds sum leave one extra cycle into the second
						if ( cycle_counter_cpu < CPU_CLOCK ) {
							cpu_interpreter();
						}
					}

				}

				// Draw every time the draw opcode is set
				if ( cpu_original_draw_mode ) {
					if ( cpu_draw_flag ) {

						// Draw
						display_draw(frame_counter, &scene);

						// Reset the flag
						cpu_draw_flag = false;
					}
				}

				// Update timer variables
				ticker_cpu_last_time = tickers_current_time;
			}

			// ------------------------------ Ticker FPS ------------------------------ //

			// Ticker FPS (60 times per second)
			if ( ticker_fps(ticker_fps_last_time, tickers_current_time) ) {

				// Handle Keyboard
				input_keyboard();

				// Handle Delay Timer
				if ( DelayTimer > 0 ) {
					DelayTimer--;
				}

				// Handle Sound Timer
				if ( SoundTimer > 0 ) {

					if ( !playing_sound ) {
						// Start playing the beep
						SDL_PauseAudioDevice(audio_device_id, 0);
						
						// Avoid starting again when already playing the sound
						playing_sound = true;
					} 

					SoundTimer--;

				} else {

					if ( playing_sound ) {
						// Stop sound
						SDL_PauseAudioDevice(audio_device_id, 1);

						// Avoid starting again when already playing the sound
						playing_sound = false;
					}

				}

				// Draw screen
				if ( !cpu_original_draw_mode ) {
					display_draw(frame_counter, &scene);

					cpu_draw_flag = false;
					cpu_halt = false;
				}

				// Update timer variables
				ticker_fps_last_time = tickers_current_time;
			}

			
		}
	}

	//Free resources and close SDL
	sound_close();
	SDL_close();

	// Deallocate Memory
	free(game_signature);
	free(string_msg4);


	return 0;
}