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

1. Add SDL_Delay to avoid unnecessary infinite loop cycles

2. Test more games (Need SCHIP):

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

    https://johnearnest.github.io/chip8Archive/


3. Print message debug just in the end of cycle?
    printf("\t\t%s\n" , OpcMessage);

4. Build a "cycle accurate" cpu, with a 12bits address bus and 8 bit data bus for visual representations?

5. README
	- Add the usage to README
	- Add pictures to README
	- ADD test result to README

6. Duplicate or triplicate frame buffer to reduce flickering
https://www.reddit.com/r/EmuDev/comments/n9dcli/comment/gxnnzdw/

7. Add options to CLI:
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

8. Test cpu_halt and the quirk_display_wait

9. Add messages for other switches (slot 4)

10. Improve draw messages into an struct?




