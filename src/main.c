#include <math.h>
#include <raylib.h>
#include <stdio.h>
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
    SetTargetFPS(60);

    /* player */

    Texture2D player = LoadTexture("src/assets/sprites/player/sprite_sheet.png");

    const int num_frames = 5;
    const int frame_width = player.width / num_frames;
    const int frame_height = player.height;

    int current_frame = 0;

    Vector2 texture_position = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    Vector2 origin = {frame_width / 2.0f, frame_height / 2.0f};
    float player_scale = 0.5f;

    while (!WindowShouldClose()) {

        ClearBackground(BLACK);
        float screen_width = GetScreenWidth();
        float screen_height = GetScreenHeight();

        Vector2 mouse_pos = GetMousePosition();

        float angle = atan2(mouse_pos.y - texture_position.y, mouse_pos.x - texture_position.x) * (180.0f / PI);

        if (IsKeyPressed(KEY_SPACE)) {
            current_frame = (current_frame + 1) % num_frames;
        }

        Rectangle source_rect = {
            current_frame * frame_width,
            0,
            frame_width,
            frame_height,
        };

        Rectangle dest_rect = {
            texture_position.x,
            texture_position.y,
            frame_width * player_scale,
            frame_height * player_scale,
        };

        BeginDrawing();
        {
            DrawFPS(2, 2);
            /* DrawTexturePro(
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
                WHITE); */

            DrawTexturePro(player,
                           source_rect,
                           dest_rect,
                           (Vector2){
                               origin.x * player_scale,
                               origin.y * player_scale},
                           angle,
                           WHITE);
        }
        EndDrawing();
    }
    UnloadTexture(player);
    CloseWindow();

    return 0;
}
