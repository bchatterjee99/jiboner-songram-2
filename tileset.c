#include "tileset.h"

char ALIEN_SHIP_TILE[20];
char BACKGROUND_OBJECT[20];
char ALIEN_SHIP_NAME[20][20];
char SHIP_WEAPONS[20][20];
char SHIP_ARMOR[20][20];

void put_str(char* a, char* b)
{
	int i = 0;
	while(b[i] != '\0')
	{
		a[i] = b[i];
		i++;
	}
	a[i] = '\0';
}

void tileset_init()
{
	ALIEN_SHIP_TILE[0] = 'Y'; // ur-quan ?
	ALIEN_SHIP_TILE[1] = '8'; // space octopus
	ALIEN_SHIP_TILE[2] = 'O'; // jani na
	ALIEN_SHIP_TILE[3] = 'V'; // little green men
	ALIEN_SHIP_TILE[4] = 'T'; // planet express
	ALIEN_SHIP_TILE[5] = 'H'; // ...

	BACKGROUND_OBJECT[0] = ' '; // kichu nei
	BACKGROUND_OBJECT[1] = '.'; // debris
	BACKGROUND_OBJECT[2] = '*'; // star
	BACKGROUND_OBJECT[3] = ','; // asteroid

	put_str(ALIEN_SHIP_NAME[0], "ur-quan");
	put_str(ALIEN_SHIP_NAME[1], "space octopus");
	put_str(ALIEN_SHIP_NAME[2], "jani na");
	put_str(ALIEN_SHIP_NAME[3], "little green men");
	put_str(ALIEN_SHIP_NAME[4], "planet express");
	put_str(ALIEN_SHIP_NAME[5], "...");


	put_str(SHIP_WEAPONS[0], "--");
	put_str(SHIP_WEAPONS[1], "laser-weapon-1");
	put_str(SHIP_WEAPONS[2], "emp-cannon");
	put_str(SHIP_WEAPONS[3], "bio-mass-ejector");

	put_str(SHIP_ARMOR[0], "--");
	put_str(SHIP_ARMOR[1], "iron-plate-armor-1");
	put_str(SHIP_ARMOR[2], "alien-metal-armor-1");
	put_str(SHIP_ARMOR[3], "mutated-exoskeleton");

}
