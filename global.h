#ifndef GLOBAL
#define GLOBAL

#include <ncurses.h>

#define LEFT 101
#define RIGHT 102
#define UP 103
#define DOWN 104

#define NORTH_WEST 105
#define NORTH_EAST 106
#define SOUTH_WEST 107
#define SOUTH_EAST 108

#define HP_BAR 15
#define POWER_BAR 12

#define ALIEN_SHIPS_MAX 20

extern int num_row;
extern int num_col;
extern int pnum_row;
extern int pnum_col;
extern int inum_row;
extern int inum_col;
extern int hnum_row;
extern int hnum_col;
extern unsigned long time_count;
extern unsigned long debug_count;

extern WINDOW* playground;
extern WINDOW* debug;
extern WINDOW* info;
extern WINDOW* hud;

extern FILE* err;

#endif
