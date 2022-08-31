#include <stdio.h>
#include <ncurses.h>

int main()
{
	initscr();
	cbreak();
	noecho();
	FILE* err = fopen("ferr.txt", "w");
	while(1)
	{
		char ch = getch();
		mvprintw(1, 1, "%x", ch);
		refresh();
	}
	return 0;
}
