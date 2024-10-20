#include <raylib.h>
#include <string.h>

#define WINDOW_SIZE_FACTOR 60.0f

int main(int argc, char **argv) {

    bool debug_mode = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-debug") == 0) {
            debug_mode = true;
        }
    }

    /* 16:9 res */
    InitWindow(16 * WINDOW_SIZE_FACTOR, 9 * WINDOW_SIZE_FACTOR, "Recycling Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        ClearBackground(BLACK);
        float screen_width = GetScreenWidth();
        float screen_height = GetScreenHeight();

        Rectangle screen_border = {
            .x = 0,
            .y = 0,
            .width = screen_width,
            .height = screen_height,
        };

        BeginDrawing();
        {
            if (debug_mode) {
                DrawFPS(2, 2);
                DrawRectangleLines(0, 0, screen_width, screen_height, RED);
                DrawRectangleLinesEx(screen_border, 2, RED);
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
