

#include "structure.h"
#include "global.h"
#include "tileset.h"
#include "player.h"


struct player_struct player;
char ship_name[20];

void player_init()
{
	player.x = 1000;
	player.y = 1000;
	player.hp = 15;
	player.max_hp = 20;
	player.primary_weapon = 1;
	player.secondary_weapon = 2;
	player.armor = 1;
	player.power = 10;
	player.max_power = 10;
	put_str(ship_name, "aaa");
}

void player_move(int dir)
{
    switch(dir)
    {
	    case LEFT:
		player.x--;
		break;
	    case DOWN:
		player.y--;
		break;
	    case UP:
		player.y++;
		break;
	    case RIGHT:
		player.x++;
		break;

	    case NORTH_WEST:
		player.x--;
		player.y++;
		break;
	    case NORTH_EAST:
		player.x++;
		player.y++;
		break;
	    case SOUTH_WEST:
		player.x--;
		player.y--;
		break;
	    case SOUTH_EAST:
		player.x++;
		player.y--;
		break;
    }
}


void player_state_update()
{
    // temporary
    // TODO: power generation system 
    int POWER_REGEN = 1;

    if(player.power < player.max_power)
	player.power += POWER_REGEN;
}
