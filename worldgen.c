

char stars[100][100];

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
    player_pos.x = 1000;
    player_pos.y = 1000;
    gen_stars();
}

void worldgen()
{
    
}
