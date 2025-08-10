#ifndef TRASH_H
#define TRASH_H

#include "player.h"
#include <raylib.h>

#define MAX_TRASH 100

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
        float speed;
        float life_time;
        Texture texture;
        TrashTag tag;
        Rectangle target_rectangle;
} Trash;

Trash init_trash(Vector2 position,
                 Vector2 target,
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

void handle_trash_collision(Trash trash_array[], int *trash_count, Rectangle blue_trashcan,
                            Rectangle green_trashcan,
                            Rectangle red_trashcan,
                            Rectangle yellow_trashcan);

bool check_collision_trash(Trash trash, Rectangle other);

#endif // TRASH_H
