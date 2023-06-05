# CHIP-8 / CHIP-8 HIRES / SCHIP Emulator

Chip 8 emulator written in C with SDL2

## CHIP8 Status
* ![100%](https://progress-bar.dev/100) CPU Opcodes
* ![100%](https://progress-bar.dev/100) Memory
* ![100%](https://progress-bar.dev/100) Registers
* ![100%](https://progress-bar.dev/100) Graphics
* ![100%](https://progress-bar.dev/100) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## CHIP8 HiRes
* ![0%](https://progress-bar.dev/0) CPU Opcodes
* ![100%](https://progress-bar.dev/100) Memory
* ![100%](https://progress-bar.dev/100) Registers
* ![0%](https://progress-bar.dev/0) Graphics
* ![100%](https://progress-bar.dev/100) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## SCHIP Status
* ![0%](https://progress-bar.dev/0) CPU Opcodes
* ![100%](https://progress-bar.dev/100) Memory
* ![100%](https://progress-bar.dev/100) Registers
* ![0%](https://progress-bar.dev/0) Graphics
* ![100%](https://progress-bar.dev/100) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## Emulator
* ![100%](https://progress-bar.dev/100) Pause and resume emulation
* ![100%](https://progress-bar.dev/100) Reset emulation
* ![80%](https://progress-bar.dev/80) Command Line Arguments
* ![100%](https://progress-bar.dev/100) Color Themes
* ![100%](https://progress-bar.dev/100) Binary rom format support
* ![0%](https://progress-bar.dev/0) Hexadecimal rom format support
* ![90%](https://progress-bar.dev/90) Keyboard remaps
* ![0%](https://progress-bar.dev/0) Step Forward CPU Cycles for Debug
* ![0%](https://progress-bar.dev/0) Step Back (Rewind) CPU Cycles for Debug
* ![100%](https://progress-bar.dev/100) Increase and Decrease CPU Clock Speed
* ![0%](https://progress-bar.dev/0) Save States
* ![0%](https://progress-bar.dev/0) Fullscreen
* ![0%](https://progress-bar.dev/0) Emulation Status from all games I have to test

# TODO

## Compatibility

1. Test more games (Need SCHIP):

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

    https://johnearnest.github.io/chip8Archive/

2. Test again with test roms!

## Improvements

1. Build a "cycle accurate" cpu, with a 12bits address bus and 8 bit data bus for visual representations?

2. Test memory leaks on binary:
 https://www.youtube.com/watch?v=bhhDRm926qA
 leaks --atExit --list -- ./build/debug/main

3 - Review on screen message system (string_msgX)

## Display

1. Duplicate or triplicate frame buffer to reduce flickering
https://www.reddit.com/r/EmuDev/comments/n9dcli/comment/gxnnzdw/

2. Emu info, function to get all values, after a for in draw to render and draw, just this one.

3. Display keys on info

4. In case of remap, show keys on first boot

## Input

1. Add mouse map to control some games like pong

## CLI

1. Add a way to pass values to parameters like display_SCALE and CPU_CLOCK.

## Sound

1 - Add wave sound to code?


## Problems

1 - FPS 61 sometimes, review time mesurement


