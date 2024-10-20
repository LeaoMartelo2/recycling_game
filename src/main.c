#include "raylib.h"
#include <string.h>

#define WINDOW_SIZE_FACTOR 60.0f

int main(int argc, char **argv) {

    bool debug = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-debug") == 0) {
            debug = true;
        }
    }

    /* 16:9 res */
    InitWindow(16 * WINDOW_SIZE_FACTOR, 9 * WINDOW_SIZE_FACTOR, "Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        ClearBackground(BLACK);
        float screen_width = GetScreenWidth();
        float screen_height = GetScreenHeight();

        Rectangle border = {
            .x = 0,
            .y = 0,
            .width = screen_width,
            .height = screen_height,
        };

        BeginDrawing();
        {
            DrawFPS(0, 0);

            DrawRectangleLines(0, 0, screen_width, screen_height, RED);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
