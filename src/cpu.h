// Global Variables

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// Components
extern unsigned char Memory[4096];      // Memory
extern unsigned short PC;               // Program Counter
extern unsigned short Opcode;           // CPU Operation Code
extern unsigned short Stack[16];        // Stack
extern unsigned short SP;               // Stack Pointer
extern unsigned char V[16];             // V Register
extern unsigned short I;                // I Register

void Initialize();
void Show();
void Interpreter();
