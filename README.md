# CHIP8

Chip 8 emulator written in C with SDL2 (earlier stage)

# To-do

1. SCHIP

2. Sound

3. Command line arguments

4. Add SDL_Delay to avoid infinite loop unnecessary cycles

5. Add Cycle Increment function

6. read hex roms

7. Test more games (Need SCHIP):

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

    https://johnearnest.github.io/chip8Archive/


8: Print message debug just in the end of cycle?
    printf("\t\t%s\n" , OpcMessage);

9 Quirks
https://github.com/Timendus/chip8-test-suite
    Missing implementation of display wait:
    Display wait - Drawing sprites to the display waits for the vertical blank interrupt, limiting their speed to max 60 sprites per second (more information here)



