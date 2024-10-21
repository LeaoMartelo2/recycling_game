#include "player.h"
#include <raylib.h>
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

    Player player = init_player("src/assets/sprites/player/sprite_sheet.png",                 // sprite
                                5,                                                            // frame count
                                (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}, // starting pos
                                0.25f,                                                        // scale
                                0.15f,                                                        // frame time
                                10.0f);                                                       // speed

    Texture2D background = LoadTexture("src/assets/level_bg/bg_expanded.png");

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){screen_width / 2.0, screen_height / 2.0};
    camera.rotation = 0;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

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

            DrawRectangleV(player.position, (Vector2){50, 50}, RED);
            camera.target = player.position;
            camera.offset = (Vector2){screen_width / 2.0f, screen_height / 2.0f};

            if (debug_mode) {
                DrawFPS(2, 2);
            }
        }
        EndDrawing();
    }
    UnloadTexture(player.texture);
    CloseWindow();

    return 0;
}
