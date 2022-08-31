#include "structure.h"
#include "global.h"

#include "draw.h"
#include "inspect.h"


void look()
{
	int cursor_row = pnum_row/2 - 5;
	int cursor_col = pnum_col/2;
	int stop = 0;
	int skip = 0;

	while(1)
	{
		draw();
		draw_cursor(cursor_row, cursor_col);
		show_info_from_cursor(cursor_row, cursor_col, skip);

		char ch = getch();
		mvwprintw(debug, 3, 1, "   ");
		mvwprintw(debug, 3, 1, "%d", ch);
		wrefresh(debug);
		switch(ch)
		{
			case 'h':
				if(cursor_col > 4)
				cursor_col--;
				break;
			case 'j':
				if(cursor_row < pnum_row - 4)
				cursor_row++;
				break;
			case 'k':
				if(cursor_row > 3)
				cursor_row--;
				break;
			case 'l':
				if(cursor_col < pnum_col - 5)
				cursor_col++;
				break;
			case 'n':
				skip++;
				break;
			case 'p':
				skip--;
				break;
			case 'x':
				stop = 1;
				break;

			case 27:
				stop = 1;
				break;
		}
		if(stop) break;
	}
	werase(info);
	box(info, 0, 0);
	wrefresh(info);
}
