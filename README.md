# CHIP8

Chip 8 emulator written in C with SDL2 (earlier stage)

# To-do
1. Interpreter (25 of 35 opcodes implemented)
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



        