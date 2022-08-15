
void player_move(int dir)
{
    switch(dir)
    {
	    case LEFT:
		player.x--;
		break;
	    case DOWN:
		player.y--;
		break;
	    case UP:
		player.y++;
		break;
	    case RIGHT:
		player.x++;
		break;
    }
}
