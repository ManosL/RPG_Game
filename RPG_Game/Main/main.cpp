#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

#include "../Grid/Grid.hpp"
#include "../Item/Item.hpp"
#include "../Spell/Spells.hpp"
#include "../Ready/Ready.hpp"

using namespace std;

static const unsigned int WIDTH = 40;
static const unsigned int HEIGHT = 40;

void read_items(ifstream&,list<Item*>&);
void read_spells(ifstream&,list<Spell*>&);


int main(){
    Grid* gr;
    list<Item*> items_list;
    list<Spell*> spells_list;
    vector<string> names;
    vector<HeroClass> heroes_type;
    int no_of_heroes = 0;
    int pos = 0; //This is for the enum vector
    string name;

    srand(time(NULL));

    cout << "\033[2J\033[1;1H";
    
    cout << "Welcome to our RPG game!!!" << endl;
    cout << "Press p to start." << endl << endl;

    cout << "Warning: you must have Caps Lock down off in order to play." << endl;

    while(getchar_silent() != 'p'){
        //DO NOTHING
    }

    while(no_of_heroes < 1 || no_of_heroes > 3){
        cout << "\033[2J\033[1;1H";
        cout << "With how many heroes do you want to play? (1,2 or 3)" << endl;
        cin >> no_of_heroes;

        cin.clear();                    //In case someone doesn't give an integer + clearing cin buff
        cin.ignore(300,'\n');
    }

    for(int i = 0;i < no_of_heroes;i++){        //Reading names of heroes + the type whicj=h are
        name = "";
        pos = 0;

        while(name.empty()){
            cout << "\033[2J\033[1;1H";
            cout << "Give the name of your hero" << endl;
            cin >> name;
        }

        names.push_back(name);

        while(pos < 1 || pos > 3){
            cout << "\033[2J\033[1;1H";
            cout << "Choose " << name <<"'s class" << endl;
            cout << "1.Warrior" << endl;
            cout << "2.Paladin" << endl;
            cout << "3.Sorcerer" << endl;
            cout << endl << "Give the proper number of the class you want" << endl;

            cin  >> pos ;

            cin.clear();
            cin.ignore(300,'\n');
        }       

        heroes_type.push_back((HeroClass) (pos - 1));
    }

    ifstream Items_file("./generators/Items.txt");      //Opening the Item and Spell files
    ifstream Spells_file("./generators/Spells.txt");

    if(!Items_file.is_open()){
        cout << "Failed to open Items file" << endl;
        return -1;
    }

    if(!Spells_file.is_open()){
        cout << "Failed to open Spells file" << endl;
        return -1;
    }

    read_items(Items_file,items_list);              //Reading them
    read_spells(Spells_file,spells_list);


    gr = new Grid(WIDTH,HEIGHT,no_of_heroes,items_list,spells_list,names,heroes_type);  //Initializing the grid

    gr->GamePlay();


    delete gr;

    Items_file.close();
    Spells_file.close();

    for(list<Item*>::iterator it = items_list.begin();it != items_list.end();){
        delete *it;
        it = items_list.erase(it);
    }

    for(list<Spell*>::iterator it = spells_list.begin();it != spells_list.end();){
        delete *it;
        it = spells_list.erase(it);
    }

    return 0;
}

void read_items(ifstream& Items,list<Item*>& Items_list){
    string temp;            //This will be useful when I read info that is actually enum
    string name;
    int Value,minLevel;

    int WeaponDamage;
    bool WeaponIsOneHanded;

    int ArmorDefensePoints;
    body_part ArmorBodyPart;

    stat PotionIncreasedStat;
    int PotionIncreaseValue;

    Items.ignore(500,'\n');        //Ignore first line

    while(1){
        Items >> name >> Value >> minLevel >> temp;

        if(Items.eof()){
            break;
        }

        if(temp == "WEAPON"){

            Items >> WeaponDamage >> temp;

            if(temp == "TRUE"){
                WeaponIsOneHanded = true;
            }
            else
                WeaponIsOneHanded = false;

            Items_list.push_back(new Weapon(name,Value,minLevel,WeaponDamage,WeaponIsOneHanded));    
        }
        else{
            if(temp == "ARMOR"){

                Items >> ArmorDefensePoints >> temp;

                if(temp == "HEAD") ArmorBodyPart = HEAD;

                if(temp == "BODY") ArmorBodyPart = BODY;

                if(temp == "HANDS") ArmorBodyPart = HANDS;

                if(temp == "LEGS") ArmorBodyPart = LEGS;

                Items_list.push_back(new Armor(name,Value,minLevel,ArmorDefensePoints,ArmorBodyPart));
            }
            else{
                if(temp == "POTION"){

                    Items >> temp >> PotionIncreaseValue;

                    if(temp == "HEALTH") PotionIncreasedStat = HEALTH;

                    if(temp == "MAGIC") PotionIncreasedStat = MAGIC;

                    if(temp == "STRENGTH") PotionIncreasedStat = STRENGTH;

                    if(temp == "DEXTERITY") PotionIncreasedStat = DEXTERITY;

                    if(temp == " AGILITY") PotionIncreasedStat = AGILITY;

                    Items_list.push_back(new Potion(name,Value,minLevel,PotionIncreasedStat,PotionIncreaseValue));
                }
            }
        }
    }
}


void read_spells(ifstream& Spells,list<Spell*>& Spells_list){
    string temp;
    string name;
    int price,minLevel,minDamage,maxDamage,MagicRequired;
    int RoundDuration;
    double ReduceRate;

    Spells.ignore(500,'\n');        //Ignoring first line

    while(1){
        Spells  >> name >> price >> minLevel >> minDamage >> maxDamage >> MagicRequired >> RoundDuration >> temp >> ReduceRate;

        if(Spells.eof()){
            break;
        }

        if(temp == "ICE"){
            Spells_list.push_back(new IceSpell(name,price,minLevel,minDamage,maxDamage,MagicRequired,RoundDuration,ReduceRate));
        }
        else
        if(temp == "FIRE"){
            Spells_list.push_back(new FireSpell(name,price,minLevel,minDamage,maxDamage,MagicRequired,RoundDuration,ReduceRate));
        }
        else
        if(temp == "LIGHTING"){
            Spells_list.push_back(new LightingSpell(name,price,minLevel,minDamage,maxDamage,MagicRequired,RoundDuration,ReduceRate));
        }
    }
}