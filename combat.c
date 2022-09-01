#include <unistd.h>

#include "structure.h"
#include "global.h"

#include "tileset.h"
#include "player.h"
#include "worldgen.h"
#include "draw.h"
#include "combat.h"


double damage_calc(int base_damage, int armor)
{
    // double ans = base_damage - armor * lvl;
    int ans = base_damage - armor;
    return ans;
}

void explosion(int x, int y)
{
    int row, col;
    global_to_screen(x, y, &row, &col);
    for(int i=0; i<8; i++)
    {
	draw();
	draw_explosion(row, col, i);
	usleep(70000);
    }
}

void explosion_test()
{
    explosion(player.x, player.y + 5);
}

int collision_detect(int x, int y, struct entity* e)
{
    // with alien ships
    for(int i=0; i<ALIEN_SHIPS_MAX; i++)
    {
	if(!alien_ships[i].valid) continue;

	if(alien_ships[i].x == x && alien_ships[i].y == y)
	{
	    e->entity_type = 4; // alien ship
	    e->id = i;
	    e->ch = ALIEN_SHIP_TILE[alien_ships[i].type];
	    // show_info(e);
	    return 1;
	}
    }
    return 0;
}


void laser_weapon_1()
{
    int ray_pos_x = player.x;
    int ray_pos_y = player.y + 1;
    int length = 3;
    int range = 15;
    struct entity e;
    int collision_x, collision_y;

    if(player.power < 3) return;
    player.power -= 3;

    int hit = 0;
    while(range--)
    {
	draw();
	draw_ray(ray_pos_x, ray_pos_y, length);
	usleep(50000);
	for(int i=0; i<3; i++)
	{
	    // fprintf(err, "ray_pos_y + i: %d\n", ray_pos_y + i); fflush(err);
	    if(collision_detect(ray_pos_x, ray_pos_y + i, &e))
	    {
		hit = 1;
		collision_x = ray_pos_x;
		collision_y = ray_pos_y + i;
		break;
		// fprintf(err, "collision\n\n"); fflush(err);
	    }
				
	}
	if(hit) break;
	ray_pos_y++;
    }
    draw();

    if(!hit) return;

    int id;
    switch(e.entity_type)
    {
    case 4: // alien ship    
	id = e.id;
	alien_ships[id].hp -= damage_calc(5, alien_ships[id].armor_class);
	show_info(&e);
	if(alien_ships[id].hp <= 0)
	{
	    destroy_ship(id);   
	    werase(info);
	    box(info, 0, 0);
	    wrefresh(info);
	    explosion(collision_x, collision_y);
	}
	break;
    }
    
}

void attack(int type)
{
	int weapon;
	if(type == 1)
	weapon = player.primary_weapon;
	else
	weapon = player.secondary_weapon;

	switch(weapon)
	{
	case 1: // laser-weapon-1
	    laser_weapon_1();
	    break;
	}
}
