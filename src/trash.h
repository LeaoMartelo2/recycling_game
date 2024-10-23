#ifndef TRASH_H
#define TRASH_H

#include "player.h"
#include <raylib.h>

typedef enum {
    TRASH_TAG_BLUE,
    TRASH_TAG_GREEN,
    TRASH_TAG_RED,
    TRASH_TAG_YELLOW,
    TRASH_TAG_NONE
} TrashTag;

typedef struct Trash {
        Vector2 position;
        Vector2 velocity;
        float scale;
        float life_time;
        Texture texture;
        TrashTag tag;
        Rectangle bounding_box;
} Trash;

Trash init_trash(Vector2 position,
                 Vector2 target,
                 float speed,
                 Texture2D texture,
                 TrashTag tag,
                 float scale,
                 Camera2D camera);

void update_trash(Trash trash_array[],
                  int *trash_count,
                  float delta_time);

void draw_trash(Trash trash_array[],
                int trash_count,
                Camera2D camera);

void handle_global_trash_count();

bool check_collision_trash(Trash trash, Rectangle other);

#endif // TRASH_H
