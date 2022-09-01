
#include "global.h"
#include "structure.h"

#include "player.h"
#include "worldgen.h"
#include "draw.h"


void space_octopus(int id)
{

}


void ai_pre_turn()
{
    for(int i=0; i<ALIEN_SHIPS_MAX; i++)
    {
	if(!alien_ships[i].valid) continue;
	int type = alien_ships[i].type;
	switch(type)
	{
	case 0: // ur-quan
	    break;
	case 1: // space-octopus
	    // if(SPEED_CHECK)
	    space_octopus(i);
	    break;
	case 2: // jani na
	    break;

	}

    }
}

void ai_post_turn()
{
   
}
