#ifndef WORLDGEN
#define WORLDGEN

extern char background[100][100];
extern struct alien_ship_struct *alien_ships;
extern struct planet_struct* planets;
extern int planet_count;


void gen_background();

void worldgen_init();

void enemy_gen();

void worldgen();

void destroy_ship(int id);

void destroy_universe();

void look();


#endif
