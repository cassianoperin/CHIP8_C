// ---------------------------- 06 Super-CHIP 1.0 opcodes ---------------------------- //
// 00FD: Exit interpreter
// 00FE: Disable high-resolution mode
// 00FF: Enable high-resolution mode
// DXY0: Draw 16 x 16 sprite (only if high-resolution mode is enabled)
// FX75: Store V0..VX in RPL user flags (X <= 7)
// FX85: Read V0..VX from RPL user flags (X <= 7)
// ---------------------------- 04 Super-CHIP 1.1 opcodes ---------------------------- //
// 00CN: Scroll display N pixels down; in low resolution mode, N/2 pixels
// 00FB: Scroll right by 4 pixels; in low resolution mode, 2 pixels
// 00FC: Scroll left by 4 pixels; in low resolution mode, 2 pixels
// FX30: Point I to 10-byte font sprite for digit VX (only digits 0-9)

