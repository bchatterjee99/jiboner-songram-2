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

void show_info(int cursor_row, int cursor_col, int skip);

#endif
