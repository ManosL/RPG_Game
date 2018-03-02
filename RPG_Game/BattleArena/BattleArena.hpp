#ifndef __BATTLE__
#define __BATTLE__

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>

#include "../Living/Living.hpp"
#include "../Ready/Ready.hpp"

class BattleArena{

private:
    Hero** ptrHeroes ;
    const unsigned int numHeroes; //number of heroes
    Monster** ptrMonsters;
    const unsigned int numMonsters; //number of monsters
    

public:
    BattleArena(Hero**, const unsigned int&,Monster**,const unsigned int&);
    int battle();
    ~BattleArena();
};

#endif