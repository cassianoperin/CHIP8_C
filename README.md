# CHIP8

Chip 8 emulator written in C with SDL2 (earlier stage)

# To-do
1. Interpreter (33 of 35 opcodes implemented)
    Missing:
    BNNN
    Ex9E
    Non-documented: 02E4 (Tic Tac Toe)

    1.1 - Test X, Y and N as an char (byte) instead of uint16 in all opcodes
    NNN: address
    NN: 8-bit constant
    N: 4-bit constant
    X and Y: 4-bit register identifier
        unsigned int lowestNibble : 4;
        https://stackoverflow.com/questions/863575/using-nibbles-4-bits-variables-in-windows-c-c

2. Test Diplay in all games (draws out of screen???)

3. Add SDL_Delay to avoid infinite loop unnecessary cycles

4. Keep the constant file?

5. Sound

6. Command line arguments

7. Clock demo has problems with letters (02D8)

8. Game signatures and legacy modes

9. TEST12

10. read hex roms

11
Games

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

https://johnearnest.github.io/chip8Archive/
https://github.com/mattmikolay/chip-8


NEXT:
fixed 8xy4


12) check if BIGGER or BIGGER THAN IN 
// 8xy5 - SUB Vx, Vy
// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
void opc_chip8_8XY5(unsigned char x, unsigned char y) {
	if ( V[x] >= V[y] ) {



13:
opc_chip8_DXYN - varisble types 


14: test breakfree
void opc_chip8_EX9E(unsigned char x) {

	// If Key number is bigger than 16, fix it (Ex.: Breakfree game)
	if int(V[x]) >= len(Key) {


15: print message debug just in the end of cycle?
printf("\t\t%s\n" , OpcMessage);

    
16 TESTSSS
https://github.com/Timendus/chip8-test-suite
https://github.com/Timendus/silicon8/tree/main/tests