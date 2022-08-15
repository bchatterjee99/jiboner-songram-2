
struct player_struct{
    int x;
    int y;
    int height;
    int hp;
    int power;
    int armor;
};

struct player_struct player;

struct alien_ship_struct{
    int type;
    int x;
    int y;
    int hp;
    int power;
    int armor;
};


struct planet_struct{
    int size;
    char name[20];
    int type;
};
