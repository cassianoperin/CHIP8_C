#pragma once
#include <SDL2/SDL.h>

// ---------------------------------- Type Definitions ---------------------------------- //

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// Struct to render Text Messages
typedef struct {
    // Message slot 01
    SDL_Texture *message1;
    SDL_Rect message1_Rect;
    // Message slot 02
    SDL_Texture *message2;
    SDL_Rect message2_Rect;
    // Message slot 03
    SDL_Texture *message3;
    SDL_Rect message3_Rect;
    // Message slot 04
    SDL_Texture *message4;
    SDL_Rect message4_Rect;
} Scene;

// Text Render Methods for text messages
typedef enum {
    TextRenderSolid,
    TextRenderShaded,
    TextRenderBlended
} TextRenderMethod;

// Text Render Type for text messages
typedef enum {
    RENDER_LATIN1,
    RENDER_UTF8,
    RENDER_UNICODE
} RenderType;