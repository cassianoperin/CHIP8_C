#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "lib.h"

// Command Line Interface
void command_line_interface(int argc, char* args[]) {

	if ( argc == 1 || argc > 2) {
		printf("\nInvalid arguments.\n\n\t%s --help for more information\n\n", args[0]);
		exit(0);
	} else if ( argc == 2 ) {

			if ( !strcmp(args[1], "--help") ) {
				printf("\nUsage:\t%s <rom_name> || <options>\n\nOptions:\n\t--help\tPrint help menu\n", args[0]);
				exit(0);
			} else {
					filename = args[1];

					// Load ROM into Memory
					load_rom(filename,  Memory, sizeof(Memory));
					printf("Loaded game: %s\n", filename);
			}
	}

}