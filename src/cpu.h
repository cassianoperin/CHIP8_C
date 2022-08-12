// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// Global Variables

// Components
extern unsigned char Memory[4096];      // Memory
extern unsigned short PC;               // Program Counter
extern unsigned short Opcode;           // CPU Operation Code
extern unsigned short Stack[16];        // Stack
extern unsigned short SP;               // Stack Pointer
extern unsigned char  V[16];            // V Register
extern unsigned short I;                // I Register
extern unsigned char DelayTimer;		// Delay Timer
extern unsigned char SoundTimer;		// Sound Timer
// 
extern bool drawFlag;					// Send the draw to screen signal
extern bool Debug;      				// Enable debug messages
extern char OpcMessage[100];			// Debug messages

// SCHIP Specific Variables
extern bool SCHIP;
extern bool SCHIP_LORES;
extern bool SCHIP_TimerHack;              // Enable or disable SCHIP DelayTimer Hack
extern unsigned char RPL[8];              // HP-48 RPL user flags

// Key Control
extern bool SCHIP_TimerHack;              // Enable or disable SCHIP DelayTimer Hack
extern unsigned char Key[16];              // Control the Keys Pressed

void Initialize();
void Show();
void Interpreter();
