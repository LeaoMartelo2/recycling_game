#include "player.h"
#include "trash.h"
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

    Texture2D blue_trash = LoadTexture("src/assets/sprites/icons/blue.png");
    Texture2D green_trash = LoadTexture("src/assets/sprites/icons/green.png");
    Texture2D red_trash = LoadTexture("src/assets/sprites/icons/red.png");
    Texture2D yellow_trash = LoadTexture("src/assets/sprites/icons/yellow.png");
    Texture2D no_texture = {0};

    Trash trash_array[MAX_TRASH];
    int trash_count = 0;

    Rectangle red_trash_can = (Rectangle){200, 200, 50, 50};

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

    while (!WindowShouldClose()) {

        float delta_time = GetFrameTime();

        Vector2 mouse_pos = GetMousePosition();

        update_player(&player, delta_time, mouse_pos, &camera);

        handle_global_trash_count();

        Vector2 player_world_pos = GetScreenToWorld2D(player.position, camera);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && player.current_trash_type != TRASH_TOTAL) {
            if (trash_count < MAX_TRASH) {
                Texture2D trash_texture = {0};
                TrashTag trash_tag = TRASH_TAG_NONE;

                switch (player.current_trash_type) {

                case TRASH_BLUE:
                    trash_texture = blue_trash;
                    trash_tag = TRASH_TAG_BLUE;
                    break;

                case TRASH_GREEN:
                    trash_texture = green_trash;
                    trash_tag = TRASH_TAG_GREEN;
                    break;

                case TRASH_RED:
                    trash_texture = red_trash;
                    trash_tag = TRASH_TAG_RED;
                    break;

                case TRASH_YELLOW:
                    trash_texture = yellow_trash;
                    trash_tag = TRASH_TAG_YELLOW;
                    break;

                case TRASH_NONE:
                case TRASH_TOTAL:
                    trash_texture = no_texture;
                    trash_tag = TRASH_TAG_NONE;
                    break;
                }

                trash_array[trash_count] = init_trash(player_world_pos,                      // pos
                                                      GetScreenToWorld2D(mouse_pos, camera), // target
                                                      trash_texture,                         // texture
                                                      trash_tag,                             // tag
                                                      0.15f,                                 // scale
                                                      camera);                               // camera

                trash_count++;
                /*global_trash_count++;*/
            }
        }

        update_trash(trash_array, &trash_count, delta_time);

        for (int i = 0; i < trash_count; i++) {
            if (trash_array[i].tag == TRASH_TAG_RED) {
                if (check_collision_trash(trash_array[i], red_trash_can)) {
                    printf("red trash collision!\n");
                }
            }
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode2D(camera);

            DrawTextureEx(background, (Vector2){25, 0}, // pos
                          0,                            // rotation
                          0.2,                          // scale
                          WHITE);                       // tint

            draw_player(player);
            draw_trash(trash_array, trash_count, camera);

            DrawRectangleRec(red_trash_can, RED);

            /*DrawRectangleV(player.position, (Vector2){50, 50}, RED);*/

            EndMode2D();
            if (debug_mode) {

                int font_size = 20;
                Color debug_color = WHITE;

                DrawFPS(2, 2);

                DrawText(TextFormat("Player:\nX: %f\nY: %f", player.position.x, player.position.y), 30, 30, font_size, debug_color);

                DrawText(TextFormat("mouse position:\nX: %f\nY: %f", mouse_pos.x, mouse_pos.y), 30, 100, font_size, debug_color);

                Vector2 mouse_worldpos = GetScreenToWorld2D(mouse_pos, camera);

                DrawText(TextFormat("mouse world_pos:\nX: %f\nY: %f", mouse_worldpos.x, mouse_worldpos.y), 30, 170, font_size, debug_color);
            }
        }
        EndDrawing();
    }
    UnloadTexture(player.texture);
    CloseWindow();

    return 0;
}
