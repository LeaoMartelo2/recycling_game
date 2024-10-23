#include "player.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define WINDOW_SIZE_FACTOR 75.0f

#define MAX_TRASH 100

float screen_width;
float screen_height;

typedef struct Trash {
        Vector2 position;
        Vector2 velocity;
        float radius;
        float life_time;
        Texture texture;
} Trash;

Vector2 calculate_direction(Vector2 from, Vector2 to) {
    Vector2 direction = {to.x - from.x, to.y - from.y};

    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    return direction;
}

Trash init_trash(Vector2 position, Vector2 target, float speed, Texture2D texture) {
    Trash trash;
    trash.position = position;
    trash.radius = 0.25f;
    Vector2 direction = calculate_direction(position, target);
    trash.velocity = (Vector2){direction.x * speed, direction.y * speed};
    trash.life_time = 0.0f;
    trash.texture = texture;

    return trash;
}

void update_trash(Trash trash_array[], int *trash_count, float delta_time) {

    for (int i = 0; i < *trash_count; i++) {
        trash_array[i].position.x += trash_array[i].velocity.x * delta_time;
        trash_array[i].position.y += trash_array[i].velocity.y * delta_time;
        trash_array[i].life_time += delta_time;

        if (trash_array[i].life_time >= 5.0f) {
            for (int j = i; j < *trash_count - 1; j++) {
                trash_array[j] = trash_array[j + 1];
            }

            (*trash_count)--;
            i--;
        }
    }
}

void DrawTrash(Trash trash_array[], int trash_count) {
    for (int i = 0; i < trash_count; i++) {
        DrawTextureV(trash_array[i].texture, trash_array[i].position, WHITE);
    }
}

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

    Trash trash_array[MAX_TRASH];
    int trash_count = 0;
    float trash_speed = 200.0f;

    Player player = init_player("src/assets/sprites/player/sprite_sheet.png", // sprite
                                1,                                            // frame count
                                (Vector2){600.0f, 337.5f},                    // starting pos
                                1.0f,                                         // scale
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

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (trash_count < MAX_TRASH) {
                Texture2D trash_texture = {0};

                switch (player.current_trash_type) {

                case TRASH_BLUE:
                    trash_texture = blue_trash;
                    break;

                case TRASH_GREEN:
                    trash_texture = green_trash;
                    break;

                case TRASH_RED:
                    trash_texture = red_trash;
                    break;

                case TRASH_YELLOW:
                    trash_texture = yellow_trash;
                    break;

                case TRASH_TOTAL:
                    break;
                }

                trash_array[trash_count] =
                    init_trash(GetScreenToWorld2D(player.position, camera),
                               GetScreenToWorld2D(mouse_pos, camera),
                               trash_speed, trash_texture);
                trash_count++;
            }
        }

        update_trash(trash_array, &trash_count, delta_time);

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
            DrawTrash(trash_array, trash_count);

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
