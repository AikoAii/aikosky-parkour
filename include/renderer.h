#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"

// --- Fungsi Visual & UI ---
void DrawTextCentered(const char* text, int y, int fontSize, Color color);
bool DrawMinimalButton(Rectangle bounds, const char* text);

#endif