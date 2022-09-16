# CHIP8

Chip 8 emulator written in C with SDL2 (earlier stage)

# To-do

1. Use 4 bits variables in x, y and nn:
    NN: 8-bit constant
    N: 4-bit constant
    X and Y: 4-bit register identifier
        unsigned int lowestNibble : 4;
        https://stackoverflow.com/questions/863575/using-nibbles-4-bits-variables-in-windows-c-c

2. Add SDL_Delay to avoid infinite loop unnecessary cycles

3. Remove the constant file (that's been used for variables)

4. Sound

5. Command line arguments

6. Add Reset game function

7. Add Cycle Increment function

8. read hex roms

9. Test more games:

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

https://johnearnest.github.io/chip8Archive/
https://github.com/mattmikolay/chip-8

10. Check if BIGGER or BIGGER THAN IN 
// 8xy5 - SUB Vx, Vy
// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
void opc_chip8_8XY5(unsigned char x, unsigned char y) {
	if ( V[x] >= V[y] ) {

11: test breakfree game
void opc_chip8_EX9E(unsigned char x) {

	// If Key number is bigger than 16, fix it (Ex.: Breakfree game)
	if int(V[x]) >= len(Key) {


12: Print message debug just in the end of cycle?
printf("\t\t%s\n" , OpcMessage);
    
13 TESTSSS
https://github.com/Timendus/chip8-test-suite
https://github.com/Timendus/silicon8/tree/main/tests

14 Quirks
https://github.com/Timendus/chip8-test-suite
    Missing implementation of display wait:
    Display wait - Drawing sprites to the display waits for the vertical blank interrupt, limiting their speed to max 60 sprites per second (more information here)



