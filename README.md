# CHIP-8 / CHIP-8 HIRES / SCHIP Emulator

Chip 8 emulator written in C with SDL2

**CHIP-8 Space Invaders Game** | **Superchip (SCHIP) Spacefight 2091!**
:-------------------------:|:-------------------------:
<img width="380" alt="invaders" src="https://github.com/cassianoperin/CHIP8/blob/master/images/invaders.gif">  |  <img width="380" alt="invaders" src="https://github.com/cassianoperin/CHIP8/blob/master/images/spacefight2091.gif">

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
* ![0%](https://progress-bar.dev/0) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## SCHIP Status
* ![0%](https://progress-bar.dev/0) CPU Opcodes
* ![100%](https://progress-bar.dev/100) Memory
* ![100%](https://progress-bar.dev/100) Registers
* ![0%](https://progress-bar.dev/0) Graphics
* ![0%](https://progress-bar.dev/0) Qwirks
* ![100%](https://progress-bar.dev/100) Sound
## Emulator
* ![100%](https://progress-bar.dev/100) Pause and resume emulation
* ![100%](https://progress-bar.dev/100) Reset emulation
* ![80%](https://progress-bar.dev/80) Command Line Arguments
* ![100%](https://progress-bar.dev/100) Color Themes
* ![100%](https://progress-bar.dev/100) Binary rom format support
* ![0%](https://progress-bar.dev/0) Hexadecimal rom format support
* ![80%](https://progress-bar.dev/80) Keyboard remaps
* ![100%](https://progress-bar.dev/100) Step Forward CPU Cycles for Debug
* ![0%](https://progress-bar.dev/0) Step Back (Rewind) CPU Cycles for Debug
* ![100%](https://progress-bar.dev/100) Increase and Decrease CPU Clock Speed
* ![0%](https://progress-bar.dev/0) Save States
* ![0%](https://progress-bar.dev/0) Fullscreen
* ![100%](https://progress-bar.dev/100) Emulation Status from all games I have to test

## EMULATOR Usage

1. Run:

	`$./chip8 ROM_NAME <options>`


- Options:

	`--debug`	Enable Debug Mode

	`--quirk_display_wait`	Turn original draw mode (on DXYN) and not on VSYNC

	`--pause`	Start emulation with CPU Paused

	`--nosound`	Disable Sound

	`-help`		Print help menu

2. Keys
- Original COSMAC Keyboard Layout (CHIP-8):

	`1` `2` `3` `C`

	`4` `5` `6` `D`

	`7` `8` `9` `E`

	`A` `0` `B` `F`

- Original HP48SX Keyboard Layout (SuperChip):

	`7` `8` `9` `/`

	`4` `5` `6` `*`

	`1` `2` `3` `-`

	`0` `.` `_` `+`

- **Keys used in this emulator:**

	`1` `2` `3` `4`

	`Q` `W` `E` `R`

	`A` `S` `D` `F`

	`Z` `X` `C` `V`

	`P`: Pause and Resume emulation

	`5`: Decrease CPU Clock Speed

	`6`: Increase CPU Clock Speed
    
    `7`: Change Color Themes

	`8`: Print on-screen information
    
	`9`: Enable / Disable Debug Mode

	`0`: Reset

	`ESC`: Exit emulator


## EMULATOR Build Instructions

### MAC
* Install C:

	 `brew install (MAP PACKAGES!!)`

* Compile:

	`make`


## Documentation

### Chip-8
[Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#0.0)

[How to write an emulator (CHIP-8 interpreter) — Multigesture.net](http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/)

[Wikipedia - CHIP-8](https://en.wikipedia.org/wiki/CHIP-8)

[trapexit chip-8 documentation](https://github.com/trapexit/chip-8_documentation)

[Thomas Daley Wiki (Game Compatibility)](https://github.com/tomdaley92/kiwi-8/issues/9)

[David Winter Documentation](http://vanbeveren.byethost13.com/stuff/CHIP8.pdf?i=2)

[Chip-8 Database](https://chip-8.github.io/database/)

[Archive chip8.com](https://web.archive.org/web/20160401091945/http://www.chip8.com/)

[Columbia University - Columbia University](http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf)

[Tom Swan Documentation](https://github.com/TomSwan/pips-for-vips)

[Chip 8 Instruction Scheduling and Frequency](https://jackson-s.me/2019/07/13/Chip-8-Instruction-Scheduling-and-Frequency.html)


### Superchip (SCHIP)
[HP48 Superchip](https://github.com/Chromatophore/HP48-Superchip)

[SCHIP](http://devernay.free.fr/hacks/chip8/schip.txt)

[Chip-8 Reference Manual](http://chip8.sourceforge.net/chip8-1.1.pdf)


### Other Chip-8 Extensions
[CHIP‐8 Extensions Reference](https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Extensions-Reference)

[CHIP‐8 Extensions (Github)](https://chip-8.github.io/extensions/)

[Chip8 Hybrids](https://www.ngemu.com/threads/chip8-thread.114578/page-22/)

[MegaChip](https://github.com/gcsmith/gchip/blob/master/docs/megachip10.txt)


### Emulators

[Octo](https://johnearnest.github.io/Octo/)

[EMMA02 Opcodes Documentation](https://www.emma02.hobby-site.com/pseudo_chip8.html)


### Memory leak testing

Test memory leaks on binary:

	`leaks --atExit --list -- main`


## TODO

### Compatibility Tests

1. Test more games (Need SCHIP):

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

    https://johnearnest.github.io/chip8Archive/
	https://www.revival-studios.com/other.php

2. Test again with test roms!

### Improvements

1. Build a "cycle accurate" cpu, with a 12bits address bus and 8 bit data bus for visual representations?

2. Build a GUI with Dear ImGui (https://www.dearimgui.com/)

3. Migrate on-screen info to GUI

4. Create key remaps for some games

### Display

1. Duplicate or triplicate frame buffer to reduce flickering
https://www.reddit.com/r/EmuDev/comments/n9dcli/comment/gxnnzdw/

2. Emu info, function to get all values, after a for in draw to render and draw, just this one.

3. Display keys on info

4. In case of remap, show keys on first boot

### Input

1. Add mouse map to control some games like pong

### CLI

1. Add a way to pass values to parameters like display_SCALE and CPU_CLOCK

### Problems

1 - FPS 61 sometimes on vsync mode, review time measurement and detect when and why

2 - quirk_display_wait is not working well on tests

3 - Remap keys: first time pressed a remaped key, present some slow down

4 - Glitches in "Most Dangerous Game [Peter Maruhnic].ch8"
	- Print sprite
	- Print current values of screen
	- Underestand

5 - Change graphics array to dynamic
	destroy and recreate window after?
	https://stackoverflow.com/questions/3827892/how-can-i-change-the-size-of-an-array-in-c

	