#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "lib.h"


// Ticker - Use with actions that should be executed each second = 1hz
bool ticker_second(long lastTime, long currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second
	if (currentTime > lastTime + 1000000) {
		success = true;
	}
	
	return success;
}


// Ticker - Use with actions that should be executed 60 times per second = 60hz
bool ticker_fps(long lastTime, long currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second / FPS
	if (currentTime > lastTime + (1000000 / display_FPS)) {
		success = true;
	}

	return success;
}


// Ticker - Use with actions that should be executed 500 times per second = 500hz
bool ticker_cpu(long lastTime, long currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second
	if (currentTime > lastTime + (1000000 / CPU_CLOCK)) {
		success = true;
	}
	
	return success;
}


// Load rom into memory
void load_rom(char *filename, unsigned char *mem, unsigned int mem_size)
{
	int PC = 0x200;

	FILE *rom = fopen(filename, "rb");
	if (!rom) {
		fprintf(stderr, "Unable to open file '%s'!\n", filename);
		exit(1);
	}
	fread(&mem[PC], 1, mem_size - PC, rom);
	fclose(rom);

	// Print Memory
	// for(int i = 0; i < mem_size; i++)
	// 	printf("%02X ", mem[i]);
	
	printf("\n\n");
}


// Get Game Signature
char *get_game_signature(char *filename) {

	// Get the first 12 elements of memory
	char *signature = (char *)malloc(26);
	sprintf(signature, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", Memory[0x200], Memory[0x201], Memory[0x202],\
		 Memory[0x203], Memory[0x204], Memory[0x205], Memory[0x206], Memory[0x207], Memory[0x208], Memory[0x209]);

	// Sum all memory bytes
	unsigned int sum = 0;
	char sum_string[10] = "";
	for ( int i = 0x200 ; i < sizeof(Memory) ; i++ ) {
		sum += Memory[i];
	}
	sprintf(sum_string, "%d", sum);

	// Unify the 12 first bytes and the sum into the final signature
	sprintf(signature + strlen(signature), "+%s", sum_string);

	return signature;
}

// Show Emulator Cycles Per Second
void showCPS(long long unsigned int number) 
{
	// Variables
    char nstring[50];
	int str_size, ptr, i , j = 0;

	// Convert the integer into a string
    sprintf(nstring, "%llu", number);
	// Size of string
	str_size = strlen(nstring);

	// Label
	strcpy(string_msg1, "Emulator Cycles per second: ");

	// Work with First 3 digits
	ptr = str_size % 3;
	if (ptr) {
		 // Print first digits before point
		for ( i = 0 ; i < ptr ; i++ ) {      
			// printf("%c", nstring[i]); 
			strncat(string_msg1, &nstring[i], 1);
		}

		// Just print the point if number is bigguer than 3
		if ( str_size > 3) {
			// printf(".");
			strcat(string_msg1, ".");
		}
	}

	for ( i = ptr ; i < str_size ; i++ ) {      // print the rest inserting points
		// printf("%c", nstring[i]);
		strncat(string_msg1, &nstring[i], 1);
		j++;
		if ( j % 3 == 0 ) {
			if( i < (str_size-1) ) {
				strcat(string_msg1, ".");
				// printf(".");
			} 
		}
	}

	// printf("\n");
}

// Show Frames Per Second
void showFPS(int number) 
{
	int length = snprintf( NULL, 0, "%d", number );

	char temp[20];
	char fps_count[10];
	char fps_text[6] = "FPS: ";
	snprintf( fps_count, length + 1, "%d", number );

	memcpy(temp,fps_count,sizeof(fps_count));
	memcpy(fps_count,fps_text,strlen(fps_text));
	memcpy(fps_count+strlen(fps_text),temp,strlen(temp)+1);

	strcpy(string_msg3, fps_count);
}

// Show CPU Cycles Per Second (Clock)
void showCPU_CPS(int number) 
{
	int length = snprintf( NULL, 0, "%d", number );

	char temp[30];
	char cps_count[30];
	char cps_text[30] = "CPU Clock: ";
	snprintf( cps_count, length + 1, "%d", number );

	memcpy(temp,cps_count,sizeof(cps_count));
	memcpy(cps_count,cps_text,strlen(cps_text));
	memcpy(cps_count+strlen(cps_text),temp,strlen(temp)+1);

	strcat(cps_count, " Hz");

	strcpy(string_msg2, cps_count);
}

// Time measurement in Microseconds (1 Sec = 1.000.000 Microsecs.)
long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

// Check if a string contains in another
uint8_t strContains(char* string, char* toFind)
{
    uint8_t slen = strlen(string);
    uint8_t tFlen = strlen(toFind);
    uint8_t found = 0;

    if( slen >= tFlen )
    {
        for(uint8_t s=0, t=0; s<slen; s++)
        {
            do{
                if( string[s] == toFind[t] )
                {
                    if( ++found == tFlen ) return 1;
                    s++;
                    t++;
                }
                else { s -= found; found=0; t=0; }

              }while(found);
        }
        return 0;
    }
    else return -1;
}

// Strings memory allocation
void string_memory_alloc() {

	// string_msg1: on screen message slot 1
	string_msg1 = malloc(sizeof(char) * 50);
	if (!string_msg1) {
		printf("Cannot allocate memory for variable \'string_msg1\'. Exiting.\n\n");
		exit(2);
	}

	// string_msg2: on screen message slot 2
	string_msg2 = malloc(sizeof(char) * 50);
	if (!string_msg2) {
		printf("Cannot allocate memory for variable \'string_msg2\'. Exiting.\n\n");
		exit(2);
	}

	// string_msg3: on screen message slot 3
	string_msg3 = malloc(sizeof(char) * 50);
	if (!string_msg3) {
		printf("Cannot allocate memory for variable \'string_msg3\'. Exiting.\n\n");
		exit(2);
	}

	// string_msg4: on screen message slot 4
	string_msg4 = malloc(sizeof(char) * 50);
	if (!string_msg4) {
		printf("Cannot allocate memory for variable \'string_msg4\'. Exiting.\n\n");
		exit(2);
	}
}

// Strings memory release
void string_memory_free() {
	// Deallocate Memory
	free(string_msg1);
	free(string_msg2);
	free(string_msg3);
	free(string_msg4);
	free(game_signature);
}