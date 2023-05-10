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
* ![100%](https://progress-bar.dev/100) Command Line Arguments
* ![100%](https://progress-bar.dev/100) Color Themes
* ![100%](https://progress-bar.dev/100) Binary rom format support
* ![90%](https://progress-bar.dev/90) Keyboard remaps
* ![0%](https://progress-bar.dev/0) Step Forward CPU Cycles for Debug
* ![0%](https://progress-bar.dev/0) Step Back (Rewind) CPU Cycles for Debug
* ![0%](https://progress-bar.dev/0) Increase and Decrease CPU Clock Speed
* ![0%](https://progress-bar.dev/0) Save States
* ![0%](https://progress-bar.dev/0) Fullscreen
* ![0%](https://progress-bar.dev/0) Hexadecimal rom format support
* ![0%](https://progress-bar.dev/0) Emulation Status from all games I have to test

# TODO

1. Test more games (Need SCHIP):

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

    https://johnearnest.github.io/chip8Archive/

2. Build a "cycle accurate" cpu, with a 12bits address bus and 8 bit data bus for visual representations?

3. README
	- Add the usage to README
	- Add pictures to README
	- ADD test result to README

4. Duplicate or triplicate frame buffer to reduce flickering
https://www.reddit.com/r/EmuDev/comments/n9dcli/comment/gxnnzdw/

5. Add options to CLI:
if *cliSchipHack {
		CPU.SCHIP_TimerHack = true
	}

	if *cliDebug {
		CPU.Debug = true
		Global.SizeYused = 0.7 //Reserve debug screen area
	}

	if *cliDrawFlag {
		// Enable Draw at DrawFlag instead of @60Hz
		Global.OriginalDrawMode = true
	}

	if *cliHybridETI660 {
		// Enable ETI-660 Hardware mode (hybrid)
		// Store rom at 0x600 instead of default 0x200
		// The ETI 660 had 64 x 48 OR 64 x 64 with a modification
		Global.Hybrid_ETI_660_HW = true
	}

	if *cliPause {
		CPU.Pause = true
	}

	if *cliHex {
		hexFlag = true
	}

	- scale
	- clock

6. Test cpu_halt and the quirk_display_wait

7. Emu info, function to get all values, after a for in draw to render and draw, just this one.

8. Display keys on info

9. In case of remap, show keys on first boot

10. Test memory leaks
 https://www.youtube.com/watch?v=bhhDRm926qA
 leaks --atExit --list -- ./build/debug/main

 leaks Report Version: 4.0, multi-line stacks
 Process 79426: 26320 nodes malloced for 5454 KB
 Process 79426: 1 leak for 64 total leaked bytes.

 1 (64 bytes) ROOT LEAK: <CFString 0x7f7f02a13430> [64]  length: 20  "BuiltInSpeakerDevice"

11. Replace *char by char
	rc/main.h:char* filename;
	src/lib.h:char *lib_game_signature;   // Game signature to apply quirks
	src/main.c:int main( int argc, char* args[] )
	src/main.c:	// char* filename = args[1];
	src/main.c:	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/# Not Supported Platforms/Chip-8X and Hybrids/ETI660 Hybrids/Pong (ETI660 Hybrid).ch8";
	src/main.c:	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/SuperChip/Demos/Robot.ch8";
	src/main.c:	// char* filename = "/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Games/Breakout (Brix hack) [David Winter, 1997].ch8";
	src/main.c:	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Programs/Clock Program [Bill Fisher, 1981].ch8";
	src/main.c:	// char* filename = (char*)"/Users/cassiano/Vscode/CHIP8_C/#Games/Chip-8/Test_Programs/chip8-test-suite.ch8";
	src/font.h:char *string_m8usg1, *string_msg2, *string_msg3, *string_msg4, *font_path;

15. Add mouse map to control some games like pong

16 - Disable Vsync for original draw mode (SLOW) cpu_original_draw_mode (RECREATE)

178 - Review MS info menu (button 8) information when change clock

19 - When clock is modified during execution, one FPS is added permanently