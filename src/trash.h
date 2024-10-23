#ifndef TRASH_H
#define TRASH_H

#include "player.h"
#include <raylib.h>

typedef struct Trash {
        Vector2 position;
        Vector2 velocity;
        float scale;
        float life_time;
        Texture texture;
        TrashType type;
} Trash;

Trash init_trash(Vector2 position,
                 Vector2 target,
                 float speed,
                 Texture2D texture,
                 TrashType type,
                 float scale);

void update_trash(Trash trash_array[],
                  int *trash_count,
                  float delta_time,
                  Camera2D camera);

void draw_trash(Trash trash_array[],
                int trash_count,
                Camera2D camera);

void handle_global_trash_count();

#endif // TRASH_H
