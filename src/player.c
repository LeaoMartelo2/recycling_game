#include "player.h"
#include <math.h>
#include <raylib.h>

Player init_player(const char *texture_path, int total_frames, Vector2 position, float scale, float frame_time, float speed) {

    Player player;
    player.texture = LoadTexture(texture_path);
    player.position = position;
    player.total_frames = total_frames;
    player.frame_width = player.texture.width / total_frames;
    player.frame_height = player.texture.height;
    player.origin = (Vector2){player.frame_width / 2.0f, player.frame_height / 2.0f};
    player.current_frame = 0;
    player.frame_counter = 0.0f;
    player.frame_time = frame_time;
    player.scale = scale;
    player.speed = speed;

    return player;
};

void animate_player(Player *player, float delta_time) {
    player->frame_counter += delta_time;

    if (player->frame_counter >= player->frame_time) {
        player->current_frame++;

        if (player->current_frame > 4) {
            player->current_frame = 1;
        }
        player->frame_counter = 0.0f;
    }
}

void update_player(Player *player, float delta_time, Vector2 mouse_pos) {
    bool movement_key_pressed = false;

    player->angle = atan2(mouse_pos.y - player->position.y, mouse_pos.x - player->position.x) * (180.0f / PI);

    if (IsKeyDown(KEY_W)) {
        movement_key_pressed = true;
        player->position.y -= player->speed;
    }

    if (IsKeyDown(KEY_A)) {
        movement_key_pressed = true;
        player->position.x -= player->speed;
    }

    if (IsKeyDown(KEY_S)) {
        movement_key_pressed = true;
        player->position.y += player->speed;
    }

    if (IsKeyDown(KEY_D)) {
        movement_key_pressed = true;
        player->position.x += player->speed;
    }

    if (movement_key_pressed) {
        animate_player(player, delta_time);
    }

    if (!movement_key_pressed) {
        player->current_frame = 0;
        player->frame_counter = 0.0f;
    }
}

void draw_player(Player player) {
    Rectangle frame_rect = {
        player.current_frame * player.frame_width,
        0,
        player.frame_width,
        player.frame_height,
    };

    Rectangle dest_rect = {
        player.position.x,
        player.position.y,
        player.frame_width * player.scale,
        player.frame_height * player.scale,
    };

    DrawTexturePro(
        player.texture,
        frame_rect,
        dest_rect,
        (Vector2){
            player.origin.x * player.scale,
            player.origin.y * player.scale},
        player.angle,
        WHITE

    );
}
