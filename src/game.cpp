#include "game.h"

/**
 * reset status player dan dunia ke awal
 */
void ResetGame(Player &p, std::vector<GameObject> &world, float &lastY, float &lastX, Camera2D &cam) {
    p = { { -16, 650, 32, 32 }, { 0, 0 }, 40.0f, 0, 700.0f };
    world.clear();
    world.push_back({{ -400, 750, 800, 20 }, 0, true}); 
    lastY = 750;
    lastX = 0;
    cam.target = (Vector2){ 0, 650 };
}