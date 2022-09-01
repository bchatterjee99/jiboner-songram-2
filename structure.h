#ifndef STRUCTURE
#define STRUCTURE

struct player_struct{
    int x;
    int y;
    int height;
    int hp;
    int max_hp;
    int power;
    int max_power;
    int armor;
    int armor_class;
    int primary_weapon;
    int secondary_weapon;
};


struct alien_ship_struct{
    char valid;
    int type;
    int x;
    int y;
    int hp;
    int max_hp;
    int power;
    int max_power;
    int armor;
    int armor_class;
    int primary_weapon;
    int secondary_weapon;
    int turn_counter;
};

struct planet_struct{
    int size;
    char name[20];
    int type;
};

struct entity{
    int entity_type;
    // 0: kichu nei
    // 1: debris
    // 2: star
    // 3: asteroid
    // 4: alien ship
    // 5: player ship

    int id;
    unsigned long timestamp;
    char ch;
};

#endif
