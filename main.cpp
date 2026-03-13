#include "raylib.h"
#include "game.h"
#include "renderer.h"
#include <cmath>

int highScore = 0;

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 800, "Aiko Sky Parkour - Demo Edition");

    GameState currentState = MENU;
    Player player;
    std::vector<GameObject> world;
    float lastY, lastX;
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    ResetGame(player, world, lastY, lastX, camera);
    SetTargetFPS(60);

    Color bgDark = { 18, 18, 24, 255 };
    Color blockColor = { 137, 180, 250, 255 }; 
    Color spikeColor = { 243, 139, 168, 255 }; 

    while (!WindowShouldClose()) {
        camera.offset = (Vector2){ (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f + 150 };

        // --- Logika Update ---
        switch (currentState) {
            case MENU:
                if (IsKeyPressed(KEY_ENTER)) {
                    ResetGame(player, world, lastY, lastX, camera);
                    currentState = GAMEPLAY;
                }
                break;
            case SETTINGS:
                if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE)) currentState = MENU;
                break;
            case GAMEPLAY: {
                float dt = GetFrameTime();
                if (IsKeyDown(KEY_LEFT)) player.velocity.x = -PLAYER_SPEED;
                else if (IsKeyDown(KEY_RIGHT)) player.velocity.x = PLAYER_SPEED;
                else player.velocity.x = 0;

                //Pakai fisika dasar yaitu hukum Newton
                player.velocity.y += GRAVITY * dt;
                player.rect.x += player.velocity.x * dt;
                float nextY = player.rect.y + player.velocity.y * dt;
                bool grounded = false;

                //Logika pijakan (one-way collision)
                for (auto& obj : world) {
                    if (!obj.active) continue;
                    if (CheckCollisionRecs(player.rect, obj.rect)) {
                        if (obj.type >= 2) {
                            if (obj.type == 2) player.score += 200;
                            else player.timeLeft += 10.0f;
                            obj.active = false;
                        }
                        else if (player.velocity.y > 0 && (player.rect.y + player.rect.height) <= (obj.rect.y + 15)) {
                            if (obj.type == 1) {
                                currentState = GAMEOVER;
                                if (player.score > highScore) highScore = player.score;
                            } else {
                                player.rect.y = obj.rect.y - player.rect.height;
                                player.velocity.y = JUMP_FORCE;
                                grounded = true;
                                if (player.rect.y < player.highestY - 50) {
                                    player.score += 20;
                                    player.highestY = player.rect.y;
                                }
                                break;
                            }
                        }
                    }
                }
                if (!grounded) player.rect.y = nextY;
                player.timeLeft -= dt;

                //generate otomatis (Algoritma prosedural)
                while (lastY > player.rect.y - 1200) {
                    int mode = GetRandomValue(0, 3);
                    lastY -= GetRandomValue(170, 210);
                    float safeBlockX = 0;
                    if (mode == 0) {
                        safeBlockX = (lastX > 0) ? GetRandomValue(-250, -100) : GetRandomValue(100, 250);
                        world.push_back({{ safeBlockX, lastY, 120, 20 }, 0, true});
                    }
                    else if (mode == 1) {
                        float startX = GetRandomValue(-200, 0);
                        int safeIdx = GetRandomValue(0, 2);
                        for(int i=0; i<3; i++) {
                            world.push_back({{ startX + (i * 110), lastY, 90, 20 }, (i == safeIdx ? 0 : 1), true});
                            if (i == safeIdx) safeBlockX = startX + (i * 110);
                        }
                    }
                    else {
                        safeBlockX = lastX + GetRandomValue(-180, 180);
                        if (safeBlockX < -250) safeBlockX = -250;
                        if (safeBlockX > 150) safeBlockX = 150;
                        world.push_back({{ safeBlockX, lastY, 120, 20 }, 0, true});
                    }
                    lastX = safeBlockX;
                    if (GetRandomValue(0, 100) < 45) {
                        int itemType = (player.timeLeft < 15.0f || GetRandomValue(0, 100) < 20) ? 3 : 2;
                        world.push_back({{ safeBlockX + 45, lastY - 35, 30, 30 }, itemType, true});
                    }
                }
                if (player.timeLeft <= 0 || player.rect.y > camera.target.y + 800) {
                    currentState = GAMEOVER;
                    if (player.score > highScore) highScore = player.score;
                }
                if (player.rect.y < camera.target.y) camera.target.y = player.rect.y;
                if (world.size() > 150) world.erase(world.begin(), world.begin() + 20);
            } break;
            default: break;
        }

        // --- Render ---
        BeginDrawing();
        ClearBackground(bgDark);

        if (currentState == MENU) {
            DrawTextCentered("AIKOSKY PARKOUR", 180, 45, RAYWHITE);
            DrawRectangle(GetScreenWidth()/2 - 120, 235, 240, 1, Fade(RAYWHITE, 0.3f));
            float midX = GetScreenWidth()/2 - 100;
            if (DrawMinimalButton({ midX, 350, 200, 50 }, "PLAY")) {
                ResetGame(player, world, lastY, lastX, camera);
                currentState = GAMEPLAY;
            }
            if (DrawMinimalButton({ midX, 420, 200, 50 }, "SETTINGS")) currentState = SETTINGS;
            if (DrawMinimalButton({ midX, 490, 200, 50 }, "EXIT")) break;
            DrawTextCentered(TextFormat("BEST: %d", highScore), 650, 16, GOLD);
        }
        else if (currentState == SETTINGS) {
            DrawTextCentered("SETTINGS & GUIDE", 120, 30, RAYWHITE);
            int infoY = 200;
            DrawTextCentered("MISSION: ASCEND AS HIGH AS POSSIBLE", infoY, 16, RAYWHITE);
            int centerX = GetScreenWidth()/2;
            DrawRectangleRounded({ (float)centerX - 110, (float)infoY + 70, 12, 12 }, 0.2, 4, GOLD);
            DrawText("POINTS", centerX - 90, infoY + 68, 14, GRAY);
            DrawRectangleRounded({ (float)centerX - 10, (float)infoY + 70, 12, 12 }, 0.2, 4, LIME);
            DrawText("TIME", centerX + 10, infoY + 68, 14, GRAY);
            DrawRectangleRounded({ (float)centerX + 70, (float)infoY + 70, 12, 12 }, 0.2, 4, spikeColor);
            DrawText("DEATH", centerX + 90, infoY + 68, 14, GRAY);
            int ctrlY = 350;
            DrawTextCentered("CONTROLS: [ < ] [ > ] ARROWS", ctrlY + 30, 16, RAYWHITE);
            if (DrawMinimalButton({ (float)centerX - 100, 550, 200, 50 }, "BACK")) currentState = MENU;
        }
        else { // GAMEPLAY & GAMEOVER
            BeginMode2D(camera);
            for (const auto& obj : world) {
                if (!obj.active) continue;
                if (obj.type == 0) DrawRectangleRounded(obj.rect, 0.2, 4, blockColor);
                else if (obj.type == 1) {
                    DrawRectangleRounded(obj.rect, 0.2, 4, spikeColor);
                    DrawRectangleRounded({obj.rect.x + 10, obj.rect.y - 10, 15, 10}, 0.2, 4, spikeColor);
                }
                else if (obj.type == 2) DrawRectangleRounded(obj.rect, 0.5, 10, GOLD);
                else if (obj.type == 3) DrawRectangleRounded(obj.rect, 0.2, 4, LIME);
            }
            DrawRectangleRounded(player.rect, 0.2, 4, RAYWHITE);
            EndMode2D();

            DrawRectangle(0, 0, GetScreenWidth(), 70, Fade(bgDark, 0.8f));
            DrawRectangleLines(20, 20, 200, 12, RAYWHITE);
            float barWidth = (player.timeLeft / 40.0f) * 196.0f;
            DrawRectangle(22, 22, (int)fmax(0.0f, fmin(barWidth, 196.0f)), 8, player.timeLeft < 10 ? spikeColor : RAYWHITE);
            DrawText(TextFormat("%.1fs", player.timeLeft), 230, 17, 18, RAYWHITE);
            DrawText(TextFormat("SCORE: %d", player.score), 20, 40, 18, RAYWHITE);
            DrawText(TextFormat("HIGH: %d", highScore), GetScreenWidth() - 150, 25, 18, GOLD);
        }

        if (currentState == GAMEOVER) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(bgDark, 0.9f));
            DrawTextCentered("GAME OVER", GetScreenHeight()/2 - 100, 50, spikeColor);
            DrawTextCentered(TextFormat("SCORE: %d", player.score), GetScreenHeight()/2 - 20, 20, RAYWHITE);
            float midX = GetScreenWidth()/2 - 100;
            if (DrawMinimalButton({ midX, (float)GetScreenHeight()/2 + 60, 200, 50 }, "RESTART")) {
                ResetGame(player, world, lastY, lastX, camera);
                currentState = GAMEPLAY;
            }
            if (DrawMinimalButton({ midX, (float)GetScreenHeight()/2 + 130, 200, 50 }, "MENU")) currentState = MENU;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}