
unsigned long time_count;
char stars[100][100];
struct alien_ship_struct *alien_ships;
struct planet_struct* planets;
int alien_ship_count;
int planet_count;

void gen_stars()
{
    for(int i=0; i<100; i++)
	for(int j=0; j<100; j++)
	    if(rand() % 70 < 1)
		stars[i][j] = '*';
	    else
		stars[i][j] = ' ';
}


void worldgen_init()
{
    player.x = 1000;
    player.y = 1000;
    gen_stars();
    time_count = 0;
    alien_ships = (struct alien_ship_struct*)malloc(15 * sizeof(struct alien_ship_struct));
    planets = (struct planet_struct*)malloc(15 * sizeof(struct planet_struct));
    alien_ship_count = 0;

    tileset_init();
}

void enemy_gen()
{
    int x = player.x + rand()%10 - 5; 
    int y = player.y + rand()%10; 
    alien_ships[alien_ship_count].x = x;
    alien_ships[alien_ship_count].y = y;
    alien_ships[alien_ship_count].type = rand()%8;
    alien_ship_count++;
}


void worldgen()
{
    time_count++;
    if(time_count % 10 == 1)
	enemy_gen();
}


void destroy_universe()
{
    free(alien_ships);
    free(planets);
}
