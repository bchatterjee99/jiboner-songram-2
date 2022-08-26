#include <unistd.h>

#include "structure.h"
#include "global.h"

#include "player.h"
#include "draw.h"
#include "combat.h"


double damage_calc(int base_damage, int armor)
{

}

void collision_detect()
{

}

void attack(int type)
{
	int weapon;
	if(type == 1)
	weapon = player.primary_weapon;
	else
	weapon = player.secondary_weapon;

	int ray_pos_x, ray_pos_y, length, range;
	switch(weapon)
	{
		case 1: // laser-weapon-1
			ray_pos_x = player.x;
			ray_pos_y = player.y;
			length = 3;
			range = 20;
			while(range--)
			{
				// collision_detect();
				draw();
				draw_ray(ray_pos_x, ray_pos_y, length);
				usleep(10000);
				ray_pos_y++;
			}
			break;
	}
}
