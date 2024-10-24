#include "trash.h"
#include <math.h>
#include <raylib.h>

#define TRASH_LIFETIME 5.0f

int global_trash_count = 0;

Vector2 calculate_direction(Vector2 from, Vector2 to) {
    Vector2 direction = {to.x - from.x, to.y - from.y};

    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    return direction;
}

Trash init_trash(Vector2 position,
                 Vector2 target,
                 Texture2D texture,
                 TrashTag tag,
                 float scale,
                 Camera2D camera) {

    Trash trash;
    trash.position = position;
    trash.scale = scale;
    trash.speed = 500.0f;
    trash.life_time = 0.0f;
    trash.texture = texture;
    trash.tag = tag;

    Vector2 direction = calculate_direction(position, GetScreenToWorld2D(target, camera));

    trash.velocity = (Vector2){direction.x * trash.speed, direction.y * trash.speed};

    trash.target_rectangle = (Rectangle){
        position.x,
        position.y,
        texture.width * scale,
        texture.height * scale};

    return trash;
}

void update_trash(Trash *trash_array, int *trash_count, float delta_time) {
    for (int i = 0; i < *trash_count; i++) {
        trash_array[i].position.x += trash_array[i].velocity.x * delta_time;
        trash_array[i].position.y += trash_array[i].velocity.y * delta_time;

        trash_array[i].target_rectangle.x = trash_array[i].position.x;
        trash_array[i].target_rectangle.y = trash_array[i].position.y;

        trash_array[i].life_time += delta_time;

        if (trash_array[i].life_time >= TRASH_LIFETIME) {
            for (int j = i; j < *trash_count - 1; j++) {
                trash_array[j] = trash_array[j + 1];
            }
            (*trash_count)--;
            i--;
        }
    }
}

void draw_trash(Trash *trash_array, int trash_count, Camera2D camera) {
    for (int i = 0; i < trash_count; i++) {
        Vector2 screen_pos = GetWorldToScreen2D(trash_array[i].position, camera);

        /*DrawTextureEx(trash_array[i].texture, screen_pos, 0.0f, trash_array[i].scale, WHITE);*/

        Rectangle screen_rect = (Rectangle){
            screen_pos.x,
            screen_pos.y,
            trash_array[i].target_rectangle.width,
            trash_array[i].target_rectangle.height};

        DrawTexturePro(trash_array[i].texture,
                       (Rectangle){0, 0, trash_array[i].texture.width, trash_array[i].texture.height},
                       screen_rect,
                       (Vector2){0, 0},
                       0.0f,
                       WHITE);

        DrawRectangleLinesEx(screen_rect, 2, RED);
    }
}

void handle_global_trash_count() {
    if (IsKeyPressed(KEY_KP_ADD)) {
        global_trash_count++;
    }
}

bool check_collision_trash(Trash trash, Rectangle other) {
    return CheckCollisionRecs(trash.target_rectangle, other);
}
