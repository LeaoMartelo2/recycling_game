#include "player.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define WINDOW_SIZE_FACTOR 75.0f

float screen_width;
float screen_height;

int main(int argc, char **argv) {

    bool debug_mode = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-debug") == 0) {
            debug_mode = true;
        }
    }

    /* 16:9 res */
    InitWindow(16 * WINDOW_SIZE_FACTOR, 9 * WINDOW_SIZE_FACTOR, "Recycling Game");

    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();

    Player player = init_player("src/assets/sprites/player/sprite_sheet.png", // sprite
                                5,                                            // frame count
                                (Vector2){600.0f, 337.5f},                    // starting pos
                                0.25f,                                        // scale
                                0.15f,                                        // frame time
                                10.0f);                                       // speed

    Texture2D background = LoadTexture("src/assets/level_bg/bg_expanded_cut.png");

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){screen_width / 2.0, screen_height / 2.0};
    camera.rotation = 0;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    Vector2 world_pos = GetScreenToWorld2D(player.position, camera);
    printf("%f %f \n", world_pos.x, world_pos.y);

    while (!WindowShouldClose()) {

        float delta_time = GetFrameTime();

        Vector2 mouse_pos = GetMousePosition();

        update_player(&player, delta_time, mouse_pos, &camera);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode2D(camera);

            DrawTextureEx(background,
                          (Vector2){25, 0}, // pos
                          0,                // rotation
                          0.2,              // scale
                          WHITE);           // tint

            draw_player(player);

            /*DrawRectangleV(player.position, (Vector2){50, 50}, RED);*/

            EndMode2D();
            if (debug_mode) {
                DrawFPS(2, 2);

                DrawText(TextFormat("X: %f,\nY: %f", player.position.x, player.position.y),
                         5, 30, 30, RED);
            }
        }
        EndDrawing();
    }
    UnloadTexture(player.texture);
    CloseWindow();

    return 0;
}
