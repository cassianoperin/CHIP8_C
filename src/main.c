#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "main.h"
	
int main( int argc, char* args[] )
{
	// ------------ Constants ------------ //
	const float msPerFrame =  1 / (float) pal_freq; // 16 ms per frame (0.016667) on NTSC, 20ms (0,02) on PAL

	// ------------ Variables ------------ //

	// Timing
	uint64_t perfFrequency        = SDL_GetPerformanceFrequency();		// Platform independent frequency
	uint64_t msPerFrameInt        = msPerFrame * perfFrequency;			// Time per frame in the deltas format
	uint64_t timeFrameStartCount  = 0;									// Start of frame counter
	uint64_t timeFrameLastCount   = SDL_GetPerformanceCounter();		// End of frame counter
	uint64_t timeFrameDuration    = 0;									// Duration of a frame
	uint64_t timeFrameDurationSum = 0;									// Sum of all frames into a second
	uint64_t timeDeltaOperations  = 0;									// Time spent into the operations (part 1)
	uint64_t timeDeltaSleep       = 0;									// Time spent sleeping (part 2)
	int      timeFrameSleep       = 0;									// Time in ms to sleep after all frame executions
	// FPS
	uint64_t timeSecondStart      = 0;									// Measurement of time spent on last frame
	uint64_t timeSecondLast       = 0;									// Measurement of time spent on last frame

	// CPU
	float opcodesPerFrameResidualSum = 0;								// CPU clock fine adjustment

	// On screen messages
	// string_msg1 = (char *)malloc(sizeof(char) * (30 + 1));
	// string_msg2 = (char *)malloc(sizeof(char) * (9 + 1));

	// Timing debug
	bool debug_timing = false;

	// Main loop control
	quit = false;

	// --------- Initialization ---------- //

	// Initialize
	cpu_initialize();

	// Initialize Audio System
	sound_init();

	// CLI and argument validation
	command_line_interface(argc, args);

	// Load Game into Memory
	filename = args[1];
	load_rom(filename,  Memory, (sizeof(Memory) / sizeof(Memory[0])) );
	printf("Loaded game: %s\n", filename);

	// Get Game signature for Qwirks
	game_signature = get_game_signature(filename);
	printf("Signature:   %s\n", game_signature );

	// Check for Quirks
	handle_legacy_opcodes(game_signature);

	// Load Fonts
	cpu_load_fonts();

	// Keyboard remaps
	input_keyboard_remaps();

	// -------------------------- SDL Init -------------------------- //
	display_init();

	// ------------------------- Font Init -------------------------- //
	font_init(renderer);

	// Seconds Counter
	timeSecondStart = SDL_GetPerformanceCounter();

	// ----------------------- Infinite Loop  ----------------------- //
	while( !quit )
	{

		// --------------------------------- START OF SECONDs COUNTER  --------------------------------- //
		if ( timeSecondLast - timeSecondStart >= 1000000000 ){ 

			// Second Ticker validation
			printf("Second: %lld\n", timeSecondLast - timeSecondStart );

			printf ("FINAL 60FPS time: %llu\n\n", timeFrameDurationSum);

			// Window Title Message update
			char title_msg[80];
			sprintf(title_msg, "Cycles per sec.: %d\t\tFPS: %d\t\tDraws: %d   Freq: %dhz   ms: %llu", cycle_counter, frame_counter, draw_counter, pal_freq, timeFrameDurationSum);
			SDL_SetWindowTitle(window, title_msg);

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

			// --------- Reset Counters ---------- //
			// Main cycle
			cycle_counter = 0;
			// Frame
			frame = 0;
			frame_counter = 0;
			timeFrameDurationSum = 0;
			// Draws
			draw_counter = 0;
			// CPU
			cycle_counter_cpu = 0;
			// Second
			timeSecondStart = SDL_GetPerformanceCounter(); // Reset second counter
		}


		// Timing: Start frame
		timeFrameStartCount = SDL_GetPerformanceCounter();

		// Increment Cycle per second counter
		cycle_counter++;



		// --------------------------- P1: START OF FRAME OPERATIONS  --------------------------- //

		// ------------- Keyboard ------------ //
		input_keyboard();

		// ----------- Delay Timer ----------- //
		if ( DelayTimer > 0 ) {
			DelayTimer--;
		}

		// ----------- Sound Timer ----------- //
		if ( SoundTimer > 0 ) {			// Just play if sound flag is enabled
			if ( sound_enabled ) {
				if ( !playing_sound ) {
					// Start playing the beep
					SDL_PauseAudioDevice(audio_device_id, 0);
					
					// Avoid starting again when already playing the sound
					playing_sound = true;
				}
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


		// --------------- CPU --------------- //
		float opcodesPerFrame = (float)CPU_CLOCK / pal_freq;					// Opcodes per frame (float)
		// printf("Opcodes: %f\n",opcodesPerFrame);
		float opcodesPerFrameResidual = opcodesPerFrame - (int)opcodesPerFrame;	// Opcodes per frame residual
		// printf("Residual: %f\n",opcodesPerFrameResidual);
		// printf("Sum anterior: %f\n",opcodesPerFrameResidualSum);
		opcodesPerFrameResidualSum += opcodesPerFrameResidual;					// Opcode residual from last frame
		// printf("Sum: %f\n\n",opcodesPerFrameResidualSum);
		
		for( int i = 0 ; i < ( (int)opcodesPerFrame ) ; i++) {
			if ( !cpu_pause ) {

				cpu_interpreter();

				// Sum the residual to add an aditional frame if necessary
				if ( opcodesPerFrameResidualSum > 1 ) {
					cpu_interpreter();

					// Update the residual opcode sum counter
					opcodesPerFrameResidualSum = opcodesPerFrameResidualSum - 1;
				}


			}
		}
		
		// -------------- DRAW --------------- //
		// Draw screen (game and text messages)
		if ( quirk_display_wait ) {

			// Draw
			display_draw(frame, &scene);
			
		}

		// ---------------------------- P1: END OF FRAME OPERATIONS  ---------------------------- //


		// ------------------- P2: START OF FRAME OPERATIONS TIME MEASUREMENT  ------------------ //
		// Timing: Update timeFrameLastCount adding the time spent on operations
		timeFrameLastCount = SDL_GetPerformanceCounter();
		timeDeltaOperations = timeFrameLastCount - timeFrameStartCount;
		// Timing: Transform operations delta into seconds view
		float timeFrameSecondsOperations = timeDeltaOperations / (float) perfFrequency;

		// Debug Timing
		if ( debug_timing ) {
			printf("Frame: %02d OPERATIONS:\tperfFrequency: %llu\ttimeFrameStartCount: %llu\ttimeDeltaOperations: %llu\ttimeFrameDuration: %llu\ttimeFrameSecondsOperations: %fs\tmsPerFrame:%fms\n",
				frame, perfFrequency, timeFrameStartCount, timeDeltaOperations, timeFrameLastCount, timeFrameSecondsOperations, msPerFrame );
		}
		
		
		// ------------------------------ P3: START OF FRAME SLEEP  ----------------------------- //

		// if we have time remaining on this frame, sleep
		if ( timeFrameSecondsOperations <= msPerFrame ) {

			// Get the integer part of the remaining time
			timeFrameSleep = 1000 * (msPerFrame - timeFrameSecondsOperations);
			
			// I've reduced 2 ms from the sleep due to its imprecision, to avoid sleep more than the time of the frame
			// and later sleep more with fine adjustment
			if ( timeFrameSleep > 2 ) {
				SDL_Delay(timeFrameSleep - 2);

				// Count the exact ammount of time spent for the sleep function	
				uint64_t timeFrameSleepCount = SDL_GetPerformanceCounter();
				timeDeltaSleep = timeFrameSleepCount - timeFrameLastCount;
				if ( debug_timing ) {
					printf("SLEEP:\t\ttimeFrameSleep: %dms\ttimeDeltaSleep(real time spent on sleep): %llu\tTotal frame time: %llu\n",
						timeFrameSleep-2, timeDeltaSleep, timeDeltaOperations + timeDeltaSleep);
				}
			} else {
				if ( debug_timing ) {
					printf("SLEEP:\t\tNo time added\n");
				}
			}

			// If entered here, update the last frame count
			timeFrameLastCount = SDL_GetPerformanceCounter();
		}
		
		// Sum the time spent in operation + sleep to have the total cycle time
		timeFrameDuration = timeDeltaOperations + timeDeltaSleep;


		// ------------------------------ P4: START OF FINE SLEEP  ------------------------------ //
		// Use main cycle loop to have precision on frames and seconds counter
		while (timeFrameDuration < msPerFrameInt ) {
			timeFrameStartCount = SDL_GetPerformanceCounter();
			timeDeltaOperations = timeFrameStartCount - timeFrameLastCount;
			timeFrameDuration += timeDeltaOperations;
			// If entered here, update the last frame count
			timeFrameLastCount = timeFrameStartCount;

			// It will generate a LOT of logs, take care
			// if ( debug_timing ) {
			// 	// printf("FINE: Loop to spent cycle %d time: %llu\t\tTotal frame time: %llu\n", counterFrames, timeDeltaOperations, timeFrameDuration);
			// }

			// If entered here, update the cycle counter
			cycle_counter++;
		}

		// Debug Timing
		if ( debug_timing ) {
			printf("Final frame time: %llu\n\n", timeFrameDuration);
		}

		// Update the timeFrameDuration with the timing of the last cycle
		timeFrameDurationSum += timeFrameDuration;

		// // Increment frame counter
		frame ++;

		// Increment Main Loop Cycle
		// cycle++;

		// Seconds Counter
		timeSecondLast = SDL_GetPerformanceCounter();
	}

















	// //Start up SDL and create window
	// if( !display_init() )
	// {
	// 	printf( "Failed to initialize SDL!\n" );
	// }
	// else
	// {
	// 	// ------------------------------ Infinite Loop  ------------------------------ //
	// 	while( !quit )
	// 	{
	// 		// Increment main loop cycle counter
	// 		cycle++;

	// 		// Increment Cycle per second counter
	// 		cycle_counter++;

	// 		// Current time using sys/time.h
	// 		tickers_current_time = getMicrotime();


	// 		// ---------------------------- Ticker Second ---------------------------- //

	// 		if ( ticker_second(ticker_second_last_time, tickers_current_time) ) {

	// 			// At least one draw per second
	// 			display_draw(frame_counter, &scene);

	// 			if ( msg_emuinfo ) {
	// 				// -------- Message slot 1 -------- //
	// 				showCPS(cycle_counter);
	// 				font_update_msg1(renderer);

	// 				// -------- Message slot 2 -------- //
	// 				showCPU_CPS(cycle_counter_cpu);
	// 				font_update_msg2(renderer);

	// 				// -------- Message slot 3 -------- //
	// 				showFPS(frame_counter);
	// 				font_update_msg3(renderer);
	// 			} else {
	// 				// Clean messages
	// 				string_msg1 = "";
	// 				string_msg2 = "";
	// 				string_msg3 = "";
	// 			}

	// 			// Message slot 4 timer
	// 			if ( message_slot4_timer > 0 ) {
	// 				message_slot4_timer --;

	// 				// When reach zero, clear
	// 				if ( message_slot4_timer == 0 ) {
	// 					string_msg4 = "";
	// 				}
	// 			}

	// 			// Update timer variables
	// 			ticker_second_last_time = tickers_current_time;

	// 			// Cycles and FPS Measurement
	// 			char title_msg[510];
	// 			sprintf(title_msg, "CPS: %d\t\tFPS: %d\t\tCPU: %d", cycle_counter, frame_counter, cycle_counter_cpu);
	// 			SDL_SetWindowTitle(window, title_msg);

	// 			// Reset counters
	// 			if ( cycle_counter != 1 ) { // Avoid incorrect measurement on first emulator cycle
	// 				last_cycle_counter = cycle_counter;
	// 			}

	// 			cycle_counter = 0;
	// 			frame_counter = 0;
	// 			cycle_counter_cpu = 0;
	// 			sleep_counter = 0;
	// 		}


	// 		// ------------------------------ Ticker CPU ------------------------------ //

	// 		if ( ticker_cpu(ticker_cpu_last_time, tickers_current_time) ) {

	// 			if ( !cpu_pause ) {

	// 				if (!cpu_halt) {
	// 					cpu_interpreter();
	// 				}

	// 			}

	// 			// Draw every time the draw opcode is set
	// 			if ( cpu_original_draw_mode ) {
	// 				if ( cpu_draw_flag ) {

	// 					// Draw
	// 					display_draw(frame_counter, &scene);

	// 					// Reset the flag
	// 					cpu_draw_flag = false;
	// 				}
	// 			}

	// 			// Update timer variables
	// 			ticker_cpu_last_time = tickers_current_time;
	// 		}


	// 		// ------------------------------ Ticker FPS ------------------------------ //

	// 		// Ticker FPS (60 times per second)
	// 		if ( ticker_fps(ticker_fps_last_time, tickers_current_time) ) {

	// 			// Handle Keyboard
	// 			input_keyboard();

	// 			// Handle Delay Timer
	// 			if ( DelayTimer > 0 ) {
	// 				DelayTimer--;
	// 			}

	// 			// Handle Sound Timer
	// 			if ( SoundTimer > 0 ) {

	// 				if ( !playing_sound ) {
	// 					// Start playing the beep
	// 					SDL_PauseAudioDevice(audio_device_id, 0);
						
	// 					// Avoid starting again when already playing the sound
	// 					playing_sound = true;
	// 				} 

	// 				SoundTimer--;

	// 			} else {

	// 				if ( playing_sound ) {
	// 					// Stop sound
	// 					SDL_PauseAudioDevice(audio_device_id, 1);

	// 					// Avoid starting again when already playing the sound
	// 					playing_sound = false;
	// 				}

	// 			}

	// 			// Draw screen
	// 			if ( !cpu_original_draw_mode ) {
	// 				display_draw(frame_counter, &scene);

	// 				cpu_draw_flag = false;
	// 				cpu_halt = false;
	// 			}

	// 			// Update timer variables
	// 			ticker_fps_last_time = tickers_current_time;
	// 		}
			

	// 		// // ----------------------- Main Loop Cycles Control ----------------------- //

	// 		// // Infinite Loop Automatic Delay Control to avoid unnecessary cpu usage
	// 		// if ( cycle_counter % sleep_modulus == 0) {
	// 		// 	// Debug
	// 		// 	printf("last_cycle_counter: %d\n", last_cycle_counter);
	// 		// 	printf("CLOCK *2: %d\n", CPU_CLOCK *2);
	// 		// 	printf("sleep_modulus: %d\n\n", sleep_modulus);

	// 		// 	// Limit the main loop control to the necessary CPU clock frequency
	// 		// 	// Reserve at least 10 times the clock speed for the main loop
	// 		// 	if ( last_cycle_counter > (CPU_CLOCK * 1000) ) {

	// 		// 		// Calibrate the sleep modulus
	// 		// 		sleep_modulus = last_cycle_counter / (CPU_CLOCK*2);

	// 		// 		// Sleep 1ms
	// 		// 		SDL_Delay(1);
	// 		// 		sleep_counter ++;

	// 		// 	} else {
	// 		// 		// Debug
	// 		// 		printf("Limit reached last_cycle_counter: %d CPU_CLOCK: %d sleep_modulus: %d NEW last_cycle_counter: %d\n", last_cycle_counter ,CPU_CLOCK, sleep_modulus, last_cycle_counter *2 );

	// 		// 		// If it starts to became close to the limit of reserved emulator cycles per second,
	// 		// 		// increment manually the last_cycle_counter to exit this loop and ensure a safe sleep_module value.
	// 		// 		last_cycle_counter *= 10;
	// 		// 	}
				
	// 		// }
			
	// 	}
	// }

	//Free resources and close SDL
	sound_close();
	SDL_close();

	// Deallocate Memory
	free(game_signature);
	// free(string_msg1);
	// free(string_msg2);


	return 0;
}