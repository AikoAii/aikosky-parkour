#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <vector>

// --- Definisi State & Konstanta ---
enum GameState { MENU, SETTINGS, GAMEPLAY, GAMEOVER };

const float GRAVITY = 1200.0f;
const float JUMP_FORCE = -850.0f;
const float PLAYER_SPEED = 550.0f;

// --- Struktur Data ---
struct Player {
    Rectangle rect;
    Vector2 velocity;
    float timeLeft;
    int score;
    float highestY;
};

struct GameObject {
    Rectangle rect;
    int type; // 0: Aman, 1: Duri, 2: Koin, 3: Jam
    bool active;
};

// --- Fungsi Logika ---
void ResetGame(Player &p, std::vector<GameObject> &world, float &lastY, float &lastX, Camera2D &cam);

#endif