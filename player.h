#ifndef PLAYER
#define PLAYER

extern struct player_struct player;

extern char ship_name[20];

void player_init();

void player_move(int dir);

void attack(int type);

void player_state_update();

#endif
