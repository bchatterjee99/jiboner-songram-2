


/* void draw() */
/* { */
/*     FILE* fp = fopen("pilot.txt", "r"); */
/*     int row = 1, col = 1; */
/*     while(1) */
/*     { */
/* 	char ch = fgetc(fp); */
/* 	if(ch == EOF) break; */
/* 	// fprintf(err, "%c", ch); */
/* 	fprintf(err, "%d: %c -- %d\n", ch, ch, '\n'); */
/* 	if(ch == '\n') */
/* 	{ */
/* 	    row++; */
/* 	    col = 1; */
/* 	    continue; */
/* 	} */
/* 	mvwaddch(playground, row, col, ch); */
/* 	col++; */
/*     } */
/*     wrefresh(playground); */
/* } */


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

	fprintf(err, "draw_alien_ship(): row: %d, col: %d, type: %d, tile: %c\n", row, col, alien_ships[i].type, ALIEN_SHIP_TILE[alien_ships[i].type]);

	mvwaddch(playground, row, col, ALIEN_SHIP_TILE[alien_ships[i].type]);
    }
}

void draw()
{
    werase(playground);
    int starty = player.y % 100;
    int startx = player.x % 100;

    starty = (starty + 100) % 100;
    startx = (startx + 100) % 100;

    int currx, curry;

    fprintf(err, "startx: %d  starty: %d\n", startx, starty);

    curry = starty;
    for(int i=2; i<pnum_row; i++)
    {
	currx = startx;
	for(int j=2; j<pnum_col; j++)
	{

	    mvwaddch(playground, i, j, stars[curry][currx]);
	    currx = (currx + 1) % 100;
	}
	curry = (curry + 1) % 100;
    }

    draw_alien_ships();

    box(playground, 0, 0);
    wrefresh(playground);
}
