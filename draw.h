#ifndef DRAW
#define DRAW

extern struct entity on_screen_object[100][100];

int inside(int row, int col);

void draw_init();

// draw tile with global coordinates
void draw_tile(int x, int y, char tile);

void draw_alien_ships();

void draw_player_ship();

void draw_hud();

void draw();

void draw_ray(int ray_pos_x, int ray_pos_y, int length);

void draw_cursor(int cursor_row, int cursor_col);

void show_info_from_cursor(int cursor_row, int cursor_col, int skip);

void show_info(struct entity* e);

void draw_explosion(int row, int col, int stage);

#endif
