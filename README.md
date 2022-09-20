# CHIP-8 / CHIP-8 HIRES / SCHIP Emulator

Chip 8 emulator written in C with SDL2 (earlier stage)

## CHIP8 Status
* ![100%](https://progress-bar.dev/100) CPU Opcodes
* ![100%](https://progress-bar.dev/100) Memory
* ![100%](https://progress-bar.dev/100) Registers
* ![100%](https://progress-bar.dev/100) Graphics
* ![90%](https://progress-bar.dev/90) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## CHIP8 HiRes
* ![0%](https://progress-bar.dev/0) CPU Opcodes
* ![100%](https://progress-bar.dev/100) Memory
* ![100%](https://progress-bar.dev/100) Registers
* ![0%](https://progress-bar.dev/0) Graphics
* ![90%](https://progress-bar.dev/90) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## SCHIP Status
* ![0%](https://progress-bar.dev/0) CPU Opcodes
* ![100%](https://progress-bar.dev/100) Memory
* ![100%](https://progress-bar.dev/100) Registers
* ![0%](https://progress-bar.dev/0) Graphics
* ![90%](https://progress-bar.dev/90) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## Emulator
* ![100%](https://progress-bar.dev/100) Pause and resume emulation
* ![100%](https://progress-bar.dev/100) Reset emulation
* ![100%](https://progress-bar.dev/100) Command Line Arguments
* ![100%](https://progress-bar.dev/100) Color Themes
* ![100%](https://progress-bar.dev/100) Binary rom format support
* ![100%](https://progress-bar.dev/100) Keyboard remaps
* ![0%](https://progress-bar.dev/0) Step Forward CPU Cycles for Debug
* ![0%](https://progress-bar.dev/0) Step Back (Rewind) CPU Cycles for Debug
* ![0%](https://progress-bar.dev/0) Increase and Decrease CPU Clock Speed
* ![0%](https://progress-bar.dev/0) Save States
* ![0%](https://progress-bar.dev/0) Fullscreen
* ![0%](https://progress-bar.dev/0) Hexadecimal rom format support
* ![0%](https://progress-bar.dev/0) Emulation Status from all games I have to test


# TODO

1. Add SDL_Delay to avoid unnecessary infinite loop cycles

2. Test more games (Need SCHIP):

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

    https://johnearnest.github.io/chip8Archive/


3. Print message debug just in the end of cycle?
    printf("\t\t%s\n" , OpcMessage);

4. Quirks
https://github.com/Timendus/chip8-test-suite
    Missing implementation of display wait:
    Display wait - Drawing sprites to the display waits for the vertical blank interrupt, limiting their speed to max 60 sprites per second (more information here)

5. Build a "cycle accurate" cpu, with a 12bits address bus and 8 bit data bus for visual representations?

6. Add the usage to README

7. Remapped keys are freezing screen for 1 second (tank) - investigate