

#include "structure.h"
#include "global.h"

#include "tileset.h"
#include "player.h"
#include "worldgen.h"

#include "draw.h"


struct entity on_screen_object[100][100];

void draw_init()
{
	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++)
			on_screen_object[i][j].timestamp = 0xffffffff;
}

int inside(int row, int col)
{
	if(row <= 1) return 0;
	if(row >= pnum_row-2) return 0;
	if(col <= 1) return 0;
	if(col >= pnum_col-2) return 0;
	return 1;
}

// draw tile with global coordinates
void draw_tile(int x, int y, char tile)
{
	int centre_row = pnum_row/2;
	int centre_col = pnum_col/2;
	int row = centre_row - (y - player.y);
	int col = centre_col + (x - player.x);
	if(inside(row, col))
		mvwaddch(playground, row, col, tile);
}

void draw_alien_ships()
{
	int centre_row = pnum_row/2;
	int centre_col = pnum_col/2;
	for(int i=0; i<alien_ship_count; i++)
	{
		int x = alien_ships[i].x;
		int y = alien_ships[i].y;
		int row = centre_row - (y - player.y);
		int col = centre_col + (x - player.x);
		// fprintf(err, "draw_alien_ship(): row: %d, col: %d, type: %d, tile: %c\n", row, col, alien_ships[i].type, ALIEN_SHIP_TILE[alien_ships[i].type]);
		if(!inside(row, col)) continue;

		mvwaddch(playground, row, col, ALIEN_SHIP_TILE[alien_ships[i].type]);
		on_screen_object[row][col].timestamp = time_count;
		on_screen_object[row][col].entity_type = 4;
		on_screen_object[row][col].id = alien_ships[i].type;
		on_screen_object[row][col].ch = ALIEN_SHIP_TILE[alien_ships[i].type];
	}
}

void draw_player_ship()
{
	int centre_row = pnum_row/2;
	int centre_col = pnum_col/2;
	mvwaddch(playground, centre_row, centre_col, PLAYER_SHIP_TILE);
	on_screen_object[centre_row][centre_col].entity_type = 5; // player ship
	on_screen_object[centre_row][centre_col].id = 0;
	on_screen_object[centre_row][centre_col].timestamp = time_count;
	on_screen_object[centre_row][centre_col].ch = PLAYER_SHIP_TILE;
}

void draw_hud()
{
	werase(hud);
	box(hud, 0, 0);

	mvwprintw(hud, 2, 2, "HP: %d/%d", player.hp, player.max_hp);
	mvwprintw(hud, 3, 2, "Power: %d/%d", player.power, player.max_power);
	mvwprintw(hud, 4, 2, "PW:"); 
	mvwprintw(hud, 5, 2, "%s", SHIP_WEAPONS[player.primary_weapon]); 
	mvwprintw(hud, 6, 2, "SW:");
	mvwprintw(hud, 7, 2, "%s", SHIP_WEAPONS[player.secondary_weapon]); 

	wrefresh(hud);
}

void draw()
{
	werase(playground);
	box(playground, 0, 0);

	int starty = player.y % 100; starty = (starty + 100) % 100;
	int startx = player.x % 100; startx = (startx + 100) % 100;
	starty = 99 - starty;

	int currx, curry;

	fprintf(err, "startx: %d  starty: %d\n", startx, starty); fflush(stderr);

	// background
	curry = starty;
	for(int i=2; i<pnum_row-2; i++)
	{
		currx = startx;
		for(int j=2; j<pnum_col-2; j++)
		{
			mvwaddch(playground, i, j, BACKGROUND_OBJECT[background[curry][currx]]);
			if(background[curry][currx] > 0)
			{
				on_screen_object[i][j].entity_type = background[curry][currx];
				on_screen_object[i][j].timestamp = time_count;
				on_screen_object[i][j].ch = BACKGROUND_OBJECT[background[curry][currx]];
			}

			currx = (currx + 1) % 100;
		}
		curry = (curry + 1) % 100;
	}

	draw_alien_ships();
	draw_player_ship();

	// box(playground, 0, 0);
	draw_hud();
	wrefresh(playground);
}

void draw_ray(int ray_pos_x, int ray_pos_y, int length)
{
	for(int i=0; i<length; i++)
		draw_tile(ray_pos_x, ray_pos_y + i, '|');
	wrefresh(playground);
}

void draw_cursor(int cursor_row, int cursor_col)
{
	int row, col;

	row = cursor_row - 2;
	for(col = cursor_col - 2; col <= cursor_col + 2; col++)
		mvwaddch(playground, row, col, '-');
	
	for(row = cursor_row - 1; row <= cursor_row + 1; row++)
	{
		mvwaddch(playground, row, cursor_col - 3, '|');
		mvwaddch(playground, row, cursor_col + 3, '|');
	}

	row = cursor_row + 2;
	for(col = cursor_col - 2; col <= cursor_col + 2; col++)
		mvwaddch(playground, row, col, '-');

	wrefresh(playground);
}

void show_info(int cursor_row, int cursor_col, int skip)
{
	werase(info);
	box(info, 0, 0);

	int num_objects = 0;
	for(int r=cursor_row-1; r<=cursor_row+1; r++)
		for(int c=cursor_col-2; c<=cursor_col+2; c++)
			if(on_screen_object[r][c].timestamp == time_count)
				num_objects++;

	if(num_objects == 0)
	{
		wrefresh(info);
		return;
	}

	skip = skip % num_objects; skip = (num_objects + skip) % num_objects;


	int ok = 0; int i,j;
	for(i=cursor_row-1; i<=cursor_row+1; i++)
	{
		for(j=cursor_col-2; j<=cursor_col+2; j++)
		{
			if(on_screen_object[i][j].timestamp == time_count)
			{
				if(skip > 0) 
				{
					skip--;
					continue;
				}
				ok = 1;
				break;
			}
		}
		if(ok) break;
	}

	int type = on_screen_object[i][j].entity_type;
	int id = on_screen_object[i][j].id;
	char ch = on_screen_object[i][j].ch;
	int filled = 0, row;
	switch(type)
	{
		case 1: // debris
			mvwprintw(info, 1, 1, "debris");
			for(int k=1; k<inum_col-1; k++) mvwaddch(info, 2, k, '-');
			break;
		case 2: // star
			mvwprintw(info, 1, 1, "unknown star");
			for(int k=1; k<inum_col-1; k++) mvwaddch(info, 2, k, '-');
			break;
		case 3: // asteroid
			mvwprintw(info, 1, 1, "asteroid");
			for(int k=1; k<inum_col-1; k++) mvwaddch(info, 2, k, '-');
			break;
		case 4: // alien ship
			row = 1;

			// name
			mvwprintw(info, row, 1, "%s", ALIEN_SHIP_NAME[id]);
			row+=1;
			for(int k=1; k<inum_col-1; k++) mvwaddch(info, row, k, '-');
			row+=1;

			// hp
			mvwprintw(info, row, 1, "HP: ");
			filled = (alien_ships[id].hp * HP_BAR)/alien_ships[id].max_hp;
			for(int k=0; k<HP_BAR; k++)
				if(k <= filled)
					mvwaddch(info, row, k + 5, '|');
				else
					mvwaddch(info, row, k + 5, '.');
			row+=1;

			// power
			mvwprintw(info, row, 1, "Power: ");
			filled = (alien_ships[id].power * POWER_BAR)/alien_ships[id].max_power;
			for(int k=0; k<POWER_BAR; k++)
				if(k <= filled)
					mvwaddch(info, row, k + 8, '|');
				else
					mvwaddch(info, row, k + 8, '.');
			row+=2;

			// primary weapon
			mvwprintw(info, row, 1, "Primary Weapon:"); row++;
			mvwprintw(info, row, 1, "%s", SHIP_WEAPONS[alien_ships[id].primary_weapon]);
			row+=2;

			// scondary weapon
			mvwprintw(info, row, 1, "Secondary Weapon:"); row++;
			mvwprintw(info, row, 1, "%s", SHIP_WEAPONS[alien_ships[id].secondary_weapon]);
			row+=2;

			// armor
			mvwprintw(info, row, 1, "Armor:"); row++;
			mvwprintw(info, row, 1, "%s", SHIP_ARMOR[alien_ships[id].armor]);

			break;

		case 5: // player ship
			row = 1;

			// name
			mvwprintw(info, row, 1, "%s", ship_name);
			row+=1;
			for(int k=1; k<inum_col-1; k++) mvwaddch(info, row, k, '-');
			row+=1;

			// hp
			mvwprintw(info, row, 1, "HP: ");
			filled = (player.hp * HP_BAR)/player.max_hp;
			for(int k=0; k<HP_BAR; k++)
				if(k <= filled)
					mvwaddch(info, row, k + 5, '|');
				else
					mvwaddch(info, row, k + 5, '.');
			row+=1;

			// power
			mvwprintw(info, row, 1, "Power: ");
			filled = (player.power * POWER_BAR)/player.max_power;
			for(int k=0; k<POWER_BAR; k++)
				if(k <= filled)
					mvwaddch(info, row, k + 8, '|');
				else
					mvwaddch(info, row, k + 8, '.');
			row+=2;

			// primary weapon
			mvwprintw(info, row, 1, "Primary Weapon:"); row++;
			mvwprintw(info, row, 1, "%s", SHIP_WEAPONS[player.primary_weapon]);
			row+=2;

			// scondary weapon
			mvwprintw(info, row, 1, "Secondary Weapon:"); row++;
			mvwprintw(info, row, 1, "%s", SHIP_WEAPONS[player.secondary_weapon]);
			row+=2;


			// armor
			mvwprintw(info, row, 1, "Armor:"); row++;
			mvwprintw(info, row, 1, "%s", SHIP_ARMOR[player.armor]);

			break;

	}
	wattron(playground, A_REVERSE);
	mvwaddch(playground, i, j, ch);
	wattroff(playground, A_REVERSE);

	wrefresh(info);
	wrefresh(playground);
}
