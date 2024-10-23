#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef enum {
    TRASH_NONE,
    TRASH_BLUE,
    TRASH_GREEN,
    TRASH_RED,
    TRASH_YELLOW,
    TRASH_TOTAL,
} TrashType;

typedef struct Player {

        Texture2D texture;
        Vector2 position;
        Vector2 origin;
        int frame_width;
        int frame_height;
        int current_frame;
        int total_frames;
        float frame_counter;
        float frame_time;
        float scale;
        float angle;
        float speed;
        TrashType current_trash_type;

} Player;

Player init_player(const char *texture_path,
                   int total_frames,
                   Vector2 position,
                   float scale,
                   float frame_time,
                   float speed);

void update_player(Player *player, float delta_time, Vector2 mouse_pos, Camera2D *camera);

void animate_player(Player *player, float delta_time);

void draw_player(Player player);

#endif // !PLAYER_H
