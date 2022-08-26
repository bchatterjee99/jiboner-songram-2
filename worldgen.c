#include <stdlib.h>

#include "structure.h"
#include "global.h"

#include "player.h"
#include "worldgen.h"


char background[100][100];
struct alien_ship_struct *alien_ships;
struct planet_struct* planets;
int alien_ship_count;
int planet_count;

void gen_background()
{
	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++)
			if(rand() % 70 < 1)
				background[i][j] = rand()%3 + 1;
			else
				background[i][j] = 0;
}


void worldgen_init()
{
	gen_background();
	time_count = 0;
	alien_ships = (struct alien_ship_struct*)malloc(15 * sizeof(struct alien_ship_struct));
	planets = (struct planet_struct*)malloc(15 * sizeof(struct planet_struct));
	alien_ship_count = 0;
}

void enemy_gen()
{
	int x = player.x + rand()%20 - 10; 
	int y = player.y + rand()%15 + 10;

	int idx = alien_ship_count;

	alien_ships[idx].x = x;
	alien_ships[idx].y = y;
	alien_ships[idx].type = rand()%3;

	switch(alien_ships[idx].type)
	{
		case 0: // ur-quan
			alien_ships[idx].hp = 10;
			alien_ships[idx].max_hp = 10;
			break;
		case 1: // space-octopus
			alien_ships[idx].hp = 15;
			alien_ships[idx].max_hp = 20;
			alien_ships[idx].power = 10;
			alien_ships[idx].max_power = 20;
			alien_ships[idx].primary_weapon = 3;
			alien_ships[idx].secondary_weapon = 0;
			alien_ships[idx].armor = 3;
			break;
		case 2: // jani na
			alien_ships[idx].hp = 15;
			alien_ships[idx].max_hp = 20;
			alien_ships[idx].power = 10;
			alien_ships[idx].max_power = 20;
			alien_ships[idx].primary_weapon = 3;
			alien_ships[idx].secondary_weapon = 0;
			alien_ships[idx].armor = 3;
			break;
	}


	alien_ship_count++;
	alien_ship_count = alien_ship_count % 15;
}


void worldgen()
{
	time_count++;
	if(time_count % 10 == 1)
		enemy_gen();
}


void destroy_universe()
{
	free(alien_ships);
	free(planets);
}



