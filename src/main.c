#include "player.h"
#include <raylib.h>
#include <string.h>

#define WINDOW_SIZE_FACTOR 75.0f

int main(int argc, char **argv) {

    bool debug_mode = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-debug") == 0) {
            debug_mode = true;
        }
    }

    /* 16:9 res */
    InitWindow(16 * WINDOW_SIZE_FACTOR, 9 * WINDOW_SIZE_FACTOR, "Recycling Game");

    Player player = init_player("src/assets/sprites/player/sprite_sheet.png",                 // sprite
                                5,                                                            // frame count
                                (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}, // starting pos
                                0.25f,                                                        // scale
                                0.15f,                                                        // frame time
                                10.0f);                                                       // speed

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        float delta_time = GetFrameTime();

        float screen_width = GetScreenWidth();
        float screen_height = GetScreenHeight();

        Vector2 mouse_pos = GetMousePosition();

        update_player(&player, delta_time, mouse_pos);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            if (debug_mode) {
                DrawFPS(2, 2);
            }

            draw_player(player);
        }
        EndDrawing();
    }
    UnloadTexture(player.texture);
    CloseWindow();

    return 0;
}
