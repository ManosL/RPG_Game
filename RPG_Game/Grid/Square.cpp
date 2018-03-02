#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "../BattleArena/BattleArena.hpp"
#include "../Ready/Ready.hpp"
#include "../Living/Living.hpp"
#include "Grid.hpp"

Grid::Square::Square(const bool& access,const bool& market,const bool& common):
isAccessible(access),hasMarket(market),isCommon(common),market(NULL)
{
    //Square constructed
}

Grid::Square::Square(const bool& access,const bool& market,const bool& common,
const std::list<Item*>& items,const std::list<Spell*>& spells):
isAccessible(access),hasMarket(market),isCommon(common), market(new Market(items,spells))
{
    //Square constructed
}

Grid::Square::~Square(){
    if(hasMarket){          ///If the square was a market square
        delete market;
    }
    else{
        //Nothing to do
    }

    //Square destroyed
}