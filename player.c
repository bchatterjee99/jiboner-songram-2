
struct player_pos_struct{
    int x;
    int y;
    int height;
};

struct player_pos_struct player_pos;


void player_move(int dir)
{
    switch(dir)
    {
	    case LEFT:
		player_pos.x--;
		break;
	    case DOWN:
		player_pos.y++;
		break;
	    case UP:
		player_pos.y--;
		break;
	    case RIGHT:
		player_pos.x++;
		break;
    }
}
