#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "../BattleArena/BattleArena.hpp"
#include "../Ready/Ready.hpp"
#include "../Living/Living.hpp"
#include "Grid.hpp"

//I write these initial values in this files because
//I want to give externally the initial stats of Livings

static const unsigned int InitialLivingMaxHealth   = 200;

static const unsigned int HeroInitialMaxMagicPower = 100;

static const unsigned int WarriorInitialStrength   = 90;
static const unsigned int WarriorInitialAgility    = 150;

static const unsigned int SorcererInitialDexterity = 150;
static const unsigned int SorcererInitialAgility   = 150;

static const unsigned int PaladinInitialStrength   = 150;
static const unsigned int PaladinInitialDexterity  = 150;

static const unsigned int HeroInitialStrength      = 80;
static const unsigned int HeroInitialDexterity     = 100;
static const unsigned int HeroInitialAgility       = 100;
static const unsigned int HeroInitialDefensePoints = 100;
static const unsigned int HeroInitialMoney         = 1000;
static const unsigned int HeroInitialLevel         = 1;
static const unsigned int HeroInitialExperience    = 0;

static  unsigned int HeroInitialPositionX;
static  unsigned int HeroInitialPositionY;

static const int MonsterInitialMaxDamage           = 90;
static const int MonsterInitialMinDamage           = 70;
static const int MonsterInitialArmor              = 70;
static const double MonsterInitialDodgePossibility = 0.1;

static const int DragonInitialMaxDamage           = 100;
static const int DragonInitialMinDamage           = 80;

static const int ExoskeletonInitialArmor         = 100;

static const double SpiritInitialDodgePossibility = 0.15;

//Rates about the map
static const double NonAccessibleRate = 0.15;
static const double MarketRate        = 0.01;
static const double CommonRate        = 1 - NonAccessibleRate - MarketRate;

//Possibility about monster being appeared
static const double BattlePossibility = 0.25;

Grid::Grid(const size_t& width_,const size_t& height_,const int& no_of_heroes_,
const std::list<Item*>& MarketItemList,const std::list<Spell*>& MarketSpellList,
const vector<string>& names,const vector<HeroClass>& heroes_class):
width(width_) , height(height_) , no_of_heroes(no_of_heroes_)
{
    //Heroes will be generating at the middle of the map
    HeroInitialPositionX  = width / 2;
    HeroInitialPositionY  = height / 2;

    //Initializing the heroes

    heroes = new Hero*[no_of_heroes];

    for(int i = 0;i < no_of_heroes;i++){

        switch(heroes_class[i]){
            case WARRIOR:
                heroes[i] = new Warrior(names[i],InitialLivingMaxHealth,HeroInitialLevel,HeroInitialMaxMagicPower,
                WarriorInitialStrength,HeroInitialDexterity,WarriorInitialAgility,HeroInitialDefensePoints,HeroInitialMoney,HeroInitialExperience,
                HeroInitialPositionX,HeroInitialPositionY);
                break;
            case PALADIN:
                heroes[i] = new Paladin(names[i],InitialLivingMaxHealth,HeroInitialLevel,HeroInitialMaxMagicPower,
                PaladinInitialStrength,PaladinInitialDexterity,HeroInitialAgility,HeroInitialDefensePoints,HeroInitialMoney,HeroInitialExperience,
                HeroInitialPositionX,HeroInitialPositionY);
                break;
            case SORCERER:
                heroes[i] = new Sorcerer(names[i],InitialLivingMaxHealth,HeroInitialLevel,HeroInitialMaxMagicPower,
                HeroInitialStrength,SorcererInitialDexterity,SorcererInitialAgility,HeroInitialDefensePoints,
                HeroInitialMoney,HeroInitialExperience,HeroInitialPositionX,HeroInitialPositionY);
                break;
        }
    }

    //Initializing the grid
    const bool isAccessible = true;
    const bool hasMarket    = true;
    const bool isCommon     = true;

    //How many aquares of each kind should I have
    unsigned int Markets        = width*height*MarketRate;
    unsigned int NonAccessibles = width*height*NonAccessibleRate;
    unsigned int Common         = width*height*CommonRate;


    if(width*height > (Markets + NonAccessibles + Common)){   //If there's any variable rounded
        Common += width*height - Markets - NonAccessibles - Common;
    }

    grid = new Square**[height];
    for(unsigned int i = 0;i < height; i++){
        grid[i] = new Square*[width];
    }

    for(unsigned int i = 0;i < height ;i++){
        for(unsigned int j = 0;j < width ;j++){
            double random_indicator;
            bool initialized = false;

            while(!initialized){                    //while the square is not initialized

                random_indicator = ((double) rand())/((double) RAND_MAX);

                if( i == HeroInitialPositionY && j == HeroInitialPositionX){        //If this is the heroes' square
                    grid[i][j] = new Square(isAccessible,!hasMarket,isCommon);
                    Common--;

                    initialized = true;
                }
                else{
                    if(random_indicator >= 0 && random_indicator <= 0.80 && Common > 0){
                        grid[i][j] = new Square(isAccessible,!hasMarket,isCommon);
                        Common--;                        

                        initialized = true;
                    }
                    else{
                        if(random_indicator > 0.80 && random_indicator <= 0.85 && Markets > 0){
                            grid[i][j] = new Square(isAccessible,hasMarket,!isCommon,MarketItemList,MarketSpellList);
                            Markets--;

                            initialized = true;
                        }
                        else{
                            if(random_indicator > 0.15 && NonAccessibles > 0){
                                grid[i][j] = new Square(!isAccessible,!hasMarket,!isCommon);
                                NonAccessibles--;

                                initialized = true;
                            }
                        }                               
                    }
                }
            }
        }
    }

    assert(Markets == 0 && NonAccessibles == 0 && Common == 0);        //Checking If I have the right number of squares 
                                                                       //of each type
}

void Grid::GamePlay(){

    BattleArena* curr_battle_arena = NULL;
    Monster** monsters = NULL;
    string temp;
    int ch = 'p';
    unsigned int hero_curr_posY = HeroInitialPositionY,hero_curr_posX = HeroInitialPositionX;
    unsigned int hero_prev_posY = HeroInitialPositionY ,hero_prev_posX = HeroInitialPositionX ; //I need this if the hero got into a market or to see if hero moved

    const int immunity_steps = height/2;                //the hero will have some immunity organize himself
    int  immunity_remaining_steps = immunity_steps ;    //at the beginning of each game or when he lost a battle to reorganize

    bool monster_appeared;
    int battle_result;
    bool quitgame = false;

    int menu_choice;
    bool pos_changed;
    bool finished_with_menu;    


    while(!quitgame){               //while I don't quit the game

        switch(ch){                 //Check which character the user pressed

            case 'w':
                if(hero_curr_posY > 0 && grid[hero_curr_posY - 1][hero_curr_posX]->isAccessibleSquare()){   //Checking if the hero can move up
                    if(immunity_remaining_steps > 0) immunity_remaining_steps--;

                       for(int i = 0;i < no_of_heroes;i++){
                        heroes[i]->Move(UP);
                        }

                }
            break;

            case 'a':
                if(hero_curr_posX > 0 && grid[hero_curr_posY][hero_curr_posX - 1]->isAccessibleSquare()){  //Checking if the hero can move left
                    if(immunity_remaining_steps > 0) immunity_remaining_steps--;

                        for(int i = 0;i < no_of_heroes;i++){
                            heroes[i]->Move(LEFT);
                        }
                        
                    }
                    break;

            case 's':
                if(hero_curr_posY < height - 1 && grid[hero_curr_posY + 1][hero_curr_posX]->isAccessibleSquare()){  //Checking if the hero can move down
                    if(immunity_remaining_steps > 0) immunity_remaining_steps--;

                    for(int i = 0;i < no_of_heroes;i++){
                        heroes[i]->Move(DOWN);
                    }
                           
                }
            break;

            case 'd':
                if(hero_curr_posX < width - 1 && grid[hero_curr_posY][hero_curr_posX + 1]->isAccessibleSquare()){ //Checking if the hero can move right
                    if(immunity_remaining_steps > 0) immunity_remaining_steps--;

                    for(int i = 0;i < no_of_heroes;i++){
                        heroes[i]->Move(RIGHT);
                    }
                          
                }
            break;

            case 'i':
                cout << "\033[2J\033[1;1H";                 //Clearing the screen
                cout << "HEROES INFO" << endl << endl;

                for(int i = 0; i < no_of_heroes;i++){
                    heroes[i]->displayStats();             //Showing heroes info
                    cout << endl << endl;
                }
                cout << endl << endl << "Press b to go back to game or q to quit game" << endl;

                while((ch = getchar_silent()) != 'b' && ch != 'q'){
                    //DO NOTHING
                }

                if(ch == 'q') quitgame = true;

            break;

            case 'm':
                cout << "\033[2J\033[1;1H";
                cout << "Full Map" << endl << endl;         //It's something like pausing the game

                displayMap();
                cout << endl << endl;
                cout << "Press b to go back or q to quit game" << endl;
                while((ch = getchar_silent()) != 'b' && ch != 'q'){
                    //DO NOTHING
                }

                if(ch == 'q') quitgame = true;

            break;

            case 'c':                           //Checking Inventory
                finished_with_menu = false;
                

                while(!finished_with_menu){
                    pos_changed = true;
                    menu_choice = 1;

                    cout << "\033[2J\033[1;1H";

                    do{
                        if(ch == 'w' && menu_choice > 1){               //Move the pointer up if you are not in the first choice
                            cout << "\033[2J\033[1;1H";
                            pos_changed = true;
                            menu_choice--;
                        }
                        else{
                            if(ch == 's' && menu_choice < no_of_heroes){    //Move the pointer down if you are not in the last choice
                                cout << "\033[2J\033[1;1H";
                                pos_changed = true;
                                menu_choice++;
                            }
                        }

                        if(pos_changed){
                            pos_changed = false;

                            cout << "For which hero do you want to see his inventory?" << endl;                 //choosing hero
                            cout << "Enter: Select" << endl << "b: Back to Game" << endl << "q: Quit Game" << endl << endl;

                            for(int i = 1;i <= no_of_heroes;i++){
                                if(i == menu_choice){
                                    cout << "->";
                                }
                                else{
                                    cout << "  ";
                                }

                                cout << heroes[i-1]->getName() << endl;
                            }
                        }
                    }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');          //Working until the user presses b,enter or q buttons

                    assert(ch == 'b' || ch == '\n' || ch == 'q');
                    if(ch == 'q'){
                        quitgame = true;                                        //quit game
                        finished_with_menu = true;
                    }
                    else{
                        if(ch == '\n'){
                            cout << "\033[2J\033[1;1H";                
                            heroes[menu_choice - 1]->CheckInventory();                      //go to the inventory of the hero the user chose
                            finished_with_menu = false;
                        }
                        else{
                            finished_with_menu = true;
                        }
                    }
                }

            break;  

            case 'q':
                quitgame = true;
            break;                          
        }

        hero_curr_posY = heroes[0]->getPositionY();         //Get the position of each hero(I take the position of first hero because all the heroes moves together)
        hero_curr_posX = heroes[0]->getPositionX();

        assert(grid[hero_curr_posY][hero_curr_posX]->isAccessibleSquare());     //check if current square is accessible

        if(grid[hero_curr_posY][hero_curr_posX]->isMarketSquare()){             //If the hero goes in a market

            cout << "\033[2J\033[1;1H";
            grid[hero_curr_posY][hero_curr_posX]->getMarket()->Interact(no_of_heroes,heroes);   //Interact with it

            for(int i = 0; i < no_of_heroes;i++){
                heroes[i]->setPositionX(hero_prev_posX);                //after interaction the heroes go to the previous square
                heroes[i]->setPositionY(hero_prev_posY);
            }

            hero_curr_posX = hero_prev_posX;
            hero_curr_posY = hero_prev_posY;
        }
        else{

            if(immunity_remaining_steps > 0 || (hero_prev_posX == hero_curr_posX && hero_prev_posY == hero_curr_posY)){     //If he is still immune and doesn't moved
                monster_appeared = false;                                                                                   //don't appear a monster
            }
            else{
                monster_appeared = ((double) rand()/(double) RAND_MAX) <= BattlePossibility ? true : false ;                //else take the possibility
            }

            if(monster_appeared){                               //If the monster appeared
                cout << "\033[2J\033[1;1H";
                cout << "Monster appeared" << endl;

                monsters = new Monster*[no_of_heroes];        //Initialize them

                for(int i = 0 ; i < no_of_heroes;i++){

                    switch(rand() % 3){
                        case 0:
                            monsters[i] = new Dragon("Dragon",InitialLivingMaxHealth,heroes[0]->getLevel(),
                            DragonInitialMinDamage,DragonInitialMaxDamage,MonsterInitialArmor,
                            MonsterInitialDodgePossibility);
                            break;
                        case 1:
                            monsters[i] = new Exoskeleton("Exoskeleton",InitialLivingMaxHealth,heroes[0]->getLevel(),
                            MonsterInitialMinDamage,MonsterInitialMaxDamage,ExoskeletonInitialArmor,
                            MonsterInitialDodgePossibility);
                            break;
                        case 2:
                            monsters[i] = new Spirit("Spirit",InitialLivingMaxHealth,heroes[0]->getLevel(),
                            MonsterInitialMinDamage,MonsterInitialMaxDamage,MonsterInitialArmor,
                            SpiritInitialDodgePossibility);
                            break;
                    }
                }

                curr_battle_arena = new BattleArena(heroes,no_of_heroes,monsters,no_of_heroes);  //Initializing the Arena

                battle_result = curr_battle_arena->battle();                                     //Beginning the battle

                if(battle_result == 0){                                                          //If heroes won
                    immunity_remaining_steps = 0;
                }
                else{                                                                           //If monsters won
                    assert(battle_result == 1);
                    immunity_remaining_steps = immunity_steps;
                }

                delete curr_battle_arena;                                                      //deleting the arena
                curr_battle_arena = NULL;
                monsters = NULL;

                monster_appeared = false;
            
            }
        }

        hero_prev_posX = hero_curr_posX;                         //Make the current pos prev
        hero_prev_posY = hero_curr_posY;

        cout << "\033[2J\033[1;1H";
        displayMap();
        //cout << immunity_remaining_steps << endl;      //just for debugging purposes   

        if(!quitgame){                      //If the user doesn't want to quit
            ch = getchar_silent();
        }
    }

    cout << "Thanks for playing" << endl;

    return;
} 

void Grid::displayMap() const{

    for(unsigned int i = 0; i < (width + 2);i++){           //Placing the bounds of the world
        cout << "#";
    }
    cout << endl;

    for(unsigned int i = 0; i < height ; i++){
        cout << "#";

        for(unsigned int j = 0; j < width ; j++){                       //If in this square is a hero print an H
            if(i == heroes[0]->getPositionY() && j == heroes[0]->getPositionX()){
                cout << "H";
            }
            else{  
                if(grid[i][j]->isAccessibleSquare()){                  
                    if(grid[i][j]->isMarketSquare()){                 //If the square has market print M
                        cout << "M";
                    }
                    else{
                        assert(grid[i][j]->isCommonSquare());       //If the square is Common just print a Space
                        cout << " ";
                    }
                }
                else{
                    cout << "X";                                    //If the square is non accessible print an X
                }
            }
        }

        cout << "#" << endl;
    }

    for(unsigned int i = 0; i < (width + 2);i++){
        cout << "#";
    }
    cout << endl;    
}


Grid::~Grid(){                              

    for(int i = 0; i < no_of_heroes; i++){  //Deleting the heroes
        delete heroes[i];
    }

    delete[] heroes;

    for(unsigned int i = 0; i < height; i++){       //Destroying the grid
        for(unsigned int j = 0; j < width; j++){
            delete grid[i][j];
        }

        delete[] grid[i];
    }

    delete[] grid;
}


