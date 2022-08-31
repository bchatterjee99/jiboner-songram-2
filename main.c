#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "structure.h"
#include "global.h"


#include "tileset.h"
#include "player.h"
#include "worldgen.h"
#include "draw.h"
#include "combat.h"
#include "inspect.h"


void init()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	refresh();

	playground = NULL;
	debug = NULL;
	info = NULL;
	hud = NULL;

	err = fopen("err1.txt", "w");
	// srand(time(0));
	srand(1);
}

void reset()
{
	getmaxyx(stdscr, num_row, num_col);

	// playground
	if(playground != NULL) delwin(playground);
	pnum_row = num_row - 2;
	pnum_col = num_col - 24;
	playground = newwin(pnum_row, pnum_col, 1, 1);
	box(playground, 0, 0);
	wrefresh(playground);

	// info
	if(info != NULL) delwin(info);
	inum_row = (num_row * 1)/2;
	inum_col = num_col - pnum_col - 2;
	info = newwin(inum_row, inum_col, 1 + 5, pnum_col + 1);
	box(info, 0, 0);
	wrefresh(info);

	// hud
	if(hud != NULL) delwin(hud);
	hnum_row = num_row - 5 - inum_row - 2;
	hnum_col = num_col - pnum_col - 2;
	hud = newwin(hnum_row, hnum_col, 1 + 5 + inum_row, pnum_col + 1);
	box(hud, 0, 0);
	wrefresh(hud);

	// debug
	if(debug != NULL) delwin(debug);
	debug = newwin(5, 15, 1, pnum_col + 1);
	box(debug, 0, 0);
	mvwprintw(debug, 1, 1, "debug:");
	mvwprintw(debug, 2, 1, "------");
	wrefresh(debug);
}


void game_loop()
{
	worldgen_init();
	draw_init();
	tileset_init();
	player_init();

	int quit = 0;
	while(1)
	{
		worldgen();
		draw();
		char ch = getch();
		mvwprintw(debug, 3, 1, "     ");
		mvwprintw(debug, 3, 1, "%d", ch);
		wrefresh(debug);
		switch(ch)
		{
			case 'h':
				player_move(LEFT);
				break;
			case 'j':
				player_move(DOWN);
				break;
			case 'k':
				player_move(UP);
				break;
			case 'l':
				player_move(RIGHT);
				break;
			case 'y':
				player_move(NORTH_WEST);
				break;
			case 'u':
				player_move(NORTH_EAST);
				break;
			case 'b':
				player_move(SOUTH_WEST);
				break;
			case 'n':
				player_move(SOUTH_EAST);
				break;


			case 'x':
				look();
				break;
			case 'a':
				attack(1); // fire primary weapon
				break;
			case 's':
				attack(2); // fire secondary weapon
				break;
			case 'e':
				explosion_test(); // test
				break;

			// faltu
			case 'r':
				reset();
				break;
			case 27:
				quit = 1;
				break;
		}
		if(quit) break;
	}
	destroy_universe();
}

/*
    Movement:           
    ---------
    y   k   u        a: primary weapon
     \  |  /
      \ | /
  h ---    --- l     s: secondary weapon
      / | \
     /  |  \
   b    j   n        x: inspect


r: reset
esc: quit
*/

int main()
{
	init();
	reset();

	game_loop();

	endwin();
	fclose(err);
	printf("\n\n  thikache\n\n");
	return 0;
}
