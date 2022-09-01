#include <stdlib.h>

#include "structure.h"
#include "global.h"

#include "player.h"
#include "worldgen.h"


char background[100][100];
struct alien_ship_struct *alien_ships;
struct planet_struct* planets;
int alien_ship_count;

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
	alien_ships = (struct alien_ship_struct*)malloc(ALIEN_SHIPS_MAX * sizeof(struct alien_ship_struct));
	planets = (struct planet_struct*)malloc(15 * sizeof(struct planet_struct));


	for(int i=0; i<ALIEN_SHIPS_MAX; i++) alien_ships[i].valid = 0;
}

void enemy_gen()
{
	int x = player.x + rand()%20 - 10; 
	int y = player.y + rand()%15 + 10;

	int idx;
	for(int i=0; i<ALIEN_SHIPS_MAX; i++)
	{
	    if(!alien_ships[i].valid)
	    {
		idx = i; break;
	    }
	}

	alien_ships[idx].valid = 1;
	alien_ships[idx].x = x;
	alien_ships[idx].y = y;
	alien_ships[idx].type = rand()%3;
	alien_ships[idx].turn_counter = 0;

	switch(alien_ships[idx].type)
	{
		case 0: // ur-quan
			alien_ships[idx].hp = 15;
			alien_ships[idx].max_hp = 15;
			alien_ships[idx].power = 10;
			alien_ships[idx].max_power = 15;
			alien_ships[idx].primary_weapon = 4; // laser-weapon-2
			alien_ships[idx].secondary_weapon = 0;
			alien_ships[idx].armor = 0;
			alien_ships[idx].armor_class = 0;
			break;
		case 1: // space-octopus
			alien_ships[idx].hp = 15;
			alien_ships[idx].max_hp = 20;
			alien_ships[idx].power = 15;
			alien_ships[idx].max_power = 20;
			alien_ships[idx].primary_weapon = 3; // bio-mass-ejector
			alien_ships[idx].secondary_weapon = 0;
			alien_ships[idx].armor = 3; // mutated-exoskeleton
			alien_ships[idx].armor_class = 2;
			break;
		case 2: // jani na
			alien_ships[idx].hp = 10;
			alien_ships[idx].max_hp = 20;
			alien_ships[idx].power = 10;
			alien_ships[idx].max_power = 20;
			alien_ships[idx].primary_weapon = 1;
			alien_ships[idx].secondary_weapon = 0;
			alien_ships[idx].armor = 4; // alien-material-armor-1
			alien_ships[idx].armor_class = 3; // alien-material-armor-1
			break;
	}

}


void worldgen()
{
	time_count++;
	if(time_count % 10 == 1)
		enemy_gen();
}


void destroy_ship(int id)
{
    alien_ships[id].valid = 0;
}

void destroy_universe()
{
	free(alien_ships);
	free(planets);
}



