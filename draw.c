


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

void draw()
{
    werase(playground);
    int starty = player_pos.y % 100;
    int startx = player_pos.x % 100;

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
    box(playground, 0, 0);
    wrefresh(playground);
}
