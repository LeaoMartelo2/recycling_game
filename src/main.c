#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <string.h>

/*#include "assets/sprites/player/player_idle.raw"*/

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
    SetTargetFPS(60);

    /*Image player_img = {*/
    /*    .data = PLAYER_EXPORT_DATA,*/
    /*    .width = PLAYER_EXPORT_WIDTH,*/
    /*    .height = PLAYER_EXPORT_HEIGHT,*/
    /*    .format = PLAYER_EXPORT_FORMAT,*/
    /*    .mipmaps = 1,*/
    /*};*/

    while (!WindowShouldClose()) {

        ClearBackground(BLACK);
        float screen_width = GetScreenWidth();
        float screen_height = GetScreenHeight();

        Vector2 mouse_pos = GetMousePosition();

        Texture2D player = LoadTexture("src/assets/sprites/player/idle_cut.png");

        Vector2 texture_position = {screen_width / 2, screen_height / 2};

        Vector2 origin = {player.width / 2.0f, player.height / 2.0f};

        float angle = atan2(mouse_pos.y - texture_position.y, mouse_pos.x - texture_position.x) * (180.0f / PI);

        float player_scale = 0.2f;

        BeginDrawing();
        {
            if (debug_mode) {
                DrawFPS(2, 2);
                printf("x: %f y:%f a:%f \n", mouse_pos.x, mouse_pos.y, angle);
            }

            DrawTexturePro(
                player,
                (Rectangle){0, 0, player.width, player.height},
                (Rectangle){
                    texture_position.x,
                    texture_position.y,
                    player.width * player_scale,
                    player.height * player_scale},
                (Vector2){
                    origin.x * player_scale,
                    origin.y * player_scale},
                angle,
                WHITE);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
