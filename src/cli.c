#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

// Command Line Interface
void command_line_interface(int argc, char* args[]) {

	// ./prog_name (1 argument)
	if ( argc == 1 ) {
		print_usage(args);

	} else if ( argc == 2 ) {	// ./main ROM.ch8 || ./main --help

		if ( strContains(args[1], "--") ) {					// --"anything"
			print_usage(args);
		} else if ( !strcmp(args[1], "--help") ) {			// --help
			print_usage(args);
		}

	// ./prog_name rom_name.ch8 (2 arguments)
	} else if ( argc > 2 ) {	// ./main ROM.ch8
			
		// Check if the first value is the rom and not an option
		if ( strContains(args[1], "--") ) {	// --"anything"
			print_usage(args);
		}

		// ./prog_name rom_name.ch8 --debug --pause (more than 2 arguments)
		for ( int i = 2 ; i < argc ; i++ ) {

			// Exit if --help in some argument
			if ( !strcmp(args[i], "--help") ) {
				print_usage(args);
			
			// Enable Debug
			} else if ( !strcmp(args[i], "--debug") ) {
				printf("Debug mode = ON\n");
				cpu_debug_mode = true;

			// Draw on DXYN
			} else if ( !strcmp(args[i], "--quirk_display_wait") ) {
				printf("Original Draw Mode = ON\n");
				quirk_display_wait = false;

			// CPU Pause mode
			} else if ( !strcmp(args[i], "--pause") ) {
				printf("Pause mode = ON\n");
				cpu_pause = true; 

			// Disable Sound
			} else if ( !strcmp(args[i], "--nosound") ) {
				printf("Sound DISABLED\n");
				sound_enabled = false; 

			// Load rom in hexadecimal format
			} else if ( !strcmp(args[i], "--hex") ) {
				printf("Hexadecimal rom mode ENABLED\n");
				rom_format_hex = true; 

			// Invalid option
			} else {
				printf("Invalid option '%s'\nExiting\n", args[i]);
				exit(0);
			}
		}
	}
}

// Print CLI usage and options
void print_usage(char* args[]) {
	printf("Usage:\t%s <rom_name> [ <options> ]\n\
		\nOptions:\
		\n\t--hex\t\t\tLoad rom into hexadecimal format\
		\n\t--help\t\t\tPrint help menu\
		\n\t--debug\t\t\tTurn on Debug Mode\
		\n\t--quirk_display_wait\tTurn original draw mode (on DXYN) and not on VSYNC\
		\n\t--pause\t\t\tStart emulation with CPU Paused\
		\n\t--nosound\t\tDisable Sound\
		\n\n", args[0]);
 
	exit(0);
}