#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>


int num_row;
int num_col;
int pnum_row;
int pnum_col;


WINDOW* playground;
WINDOW* debug;

FILE* err;


#include "constants.h"
#include "tileset.h"
#include "structure.h"
#include "player.c"
#include "worldgen.c"
#include "draw.c"


void init()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();

    playground = NULL;
    debug = NULL;

    err = fopen("err.txt", "w");

    srand(time(0));
}

void reset()
{
    getmaxyx(stdscr, num_row, num_col);

    if(playground != NULL) free(playground);
    pnum_row = num_row - 2;
    pnum_col = num_col - 10;
    playground = newwin(num_row - 2, num_col - 20, 1, 1);

    box(playground, 0, 0);
    wrefresh(playground);

    if(debug != NULL) free(debug);
    debug = newwin(5, 15, 1, num_col - 18);
    box(debug, 0, 0);
    mvwprintw(debug, 1, 1, "debug:");
    mvwprintw(debug, 2, 1, "------");
    wrefresh(debug);
}


void game_loop()
{
    worldgen_init();
    int quit = 0;
    while(1)
    {
	worldgen();
	draw();
	char ch = getch();
	mvwprintw(debug, 3, 1, "   ");
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
	    case 27:
		quit = 1;
		break;
	}
	if(quit) break;
    }
    destroy_universe();
}


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
