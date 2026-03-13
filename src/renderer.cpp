#include "renderer.h"

/**
 * Gambar teks di tengah sumbu X layar
 */
void DrawTextCentered(const char* text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, GetScreenWidth() / 2 - textWidth / 2, y, fontSize, color);
}

/**
 * Tombol 
 */
bool DrawMinimalButton(Rectangle bounds, const char* text) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, bounds);

    if (hover) {
        DrawRectangleRec(bounds, RAYWHITE);
        DrawText(text, bounds.x + (bounds.width - MeasureText(text, 20))/2, bounds.y + bounds.height/2 - 10, 20, BLACK);
    } else {
        DrawRectangleLinesEx(bounds, 2, RAYWHITE);
        DrawText(text, bounds.x + (bounds.width - MeasureText(text, 20))/2, bounds.y + bounds.height/2 - 10, 20, RAYWHITE);
    }
    return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}