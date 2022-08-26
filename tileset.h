#ifndef TILESET
#define TILESET

#define PLAYER_SHIP_TILE 'A'
extern char ALIEN_SHIP_TILE[20];
extern char BACKGROUND_OBJECT[20];
extern char ALIEN_SHIP_NAME[20][20];
extern char SHIP_WEAPONS[20][20];
extern char SHIP_ARMOR[20][20];

void put_str(char* a, char* b);

void tileset_init();

#endif
