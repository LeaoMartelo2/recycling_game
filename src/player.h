#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

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

} Player;

Player init_player(const char *texture_path,
                   int total_frames,
                   Vector2 position,
                   float scale,
                   float frame_time);

void update_player(Player *player, float delta_time, Vector2 mouse_pos);

void animate_player(Player *player, float delta_time);

void draw_player(Player player);

#endif // !PLAYER_H
