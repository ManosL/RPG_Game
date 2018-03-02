#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>

#include "../BattleArena/BattleArena.hpp"
#include "../Ready/Ready.hpp"
#include "../Living/Living.hpp"
#include "Grid.hpp"


Grid::Square::Market::Market(const list<Item*>& items,const list<Spell*>& spells)
{
    //Market constructed
    for(list<Item*>::const_iterator it = items.begin(); it != items.end(); it++){       //Copying the item list because it's a list of pointers
        switch((*it)->getType()){
            case WEAPON:
            {
                Items.push_back(new Weapon((Weapon&) **it));
            }
            break; 
            case ARMOR:
            {
                Items.push_back(new Armor((Armor&) **it));
            }
            break;
            case POTION:
            {
                Items.push_back(new Potion((Potion&) **it));
            }
        }
    }

    for(list<Spell*>::const_iterator it = spells.begin(); it != spells.end(); it++){    //Copying the list of Spells because it's list of pointers
        switch((*it)->getSpellType()){
            case ICE:
            {
                Spells.push_back(new IceSpell((IceSpell&) **it));
            }
            break;
            case FIRE:
            {
                Spells.push_back(new FireSpell((FireSpell&) **it));
            }
            break;
            case LIGHTING:
            {
                Spells.push_back(new LightingSpell((LightingSpell&) **it));
            }
            break;
        }
    }

    //I do these copies because the lists contain pointers and I have
    //more than one markets
}

//REST  MARKET FUNCTIONS TO BE WRITTEN

void Grid::Square::Market::Interact(const int& heroes_number,Hero**& Heroes){       //Main market function
    list<Item*>::const_iterator curr_item;
    list<Spell*>::const_iterator curr_spell;
    int menu_pos = 1;
    int point_pos = 1,next_point_pos;
    int prev_point_pos ;

    int ch = 'c';

    bool pos_changed = true;

    Hero* curr_hero;

    vector<string> MarketChoices;
    vector<string> BuyChoices;
    vector<string> SellChoices;


    string temp;                //In case I want to clear the buff


    MarketChoices.push_back("Buy");                     //Initializing the choice vectors
    MarketChoices.push_back("Sell");
    MarketChoices.push_back("Show Inventory");
    MarketChoices.push_back("Show Info");

    BuyChoices.push_back("Show Info");
    BuyChoices.push_back("Buy");

    SellChoices.push_back("Show Info");
    SellChoices.push_back("Sell");    

    cout << "Hello Stranger(s) " << endl << "Welcome to our Market" << endl << endl;

    while(menu_pos){                    //while I don't quit menu
        switch(menu_pos){               //Checking in which menu I am in
            case 1:
                pos_changed = true;     //flag that tells if the position of the point changed
                do{     

                    if(ch == 'w' && point_pos > 1){         //If the user is not at first choice and want to go up the point moves up
                        cout << "\033[2J\033[1;1H";
                        pos_changed = true;
                        point_pos--;
                    }
                    else{
                        if(ch == 's' && point_pos < heroes_number){ //If the user is not at last choice and want to go down the point moves down
                            cout << "\033[2J\033[1;1H";
                            pos_changed = true;
                            point_pos++;
                        }
                    }

                    if(pos_changed){
                        pos_changed = false;

                        cout << "With which hero do you want to opt for?" << endl;                  //Choosing hero
                        cout << "Enter: Select" << endl << "b: Back" << endl << "q: Quit" << endl << endl;
                        
                        for(int i = 1;i <= heroes_number;i++){
                            if(i == point_pos){
                                cout << "->";
                            }
                            else{
                                cout << "  ";
                            }

                            cout << Heroes[i-1]->getName() << endl;
                        }
                    }
                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');

                assert(ch == 'b' || ch == '\n' || ch == 'q');
                if(ch == 'b' || ch == 'q') menu_pos--;          //If the user pressed b or q now , menu quits
                else{                                           //If the user pressed enter
                    menu_pos++;                                 //I procced to next menu
                    curr_hero = (Hero*) Heroes[point_pos - 1];  //and the user's hero choice saved at curr_hero
                }

                cout << "\033[2J\033[1;1H";                     //Clearing the screen
            break;

            case 2:

                cout << "\033[2J\033[1;1H";
                pos_changed = true;                 //Initializing again these variables
                ch = 'c';

                point_pos = 1;

                do{
                    if(ch == 'w' && point_pos > 1){             //The same prosecution as the previous menu
                        cout << "\033[2J\033[1;1H";
                        pos_changed = true;
                        point_pos--;
                    }
                    else{
                        if(ch == 's' && point_pos < MarketChoices.size()){
                            cout << "\033[2J\033[1;1H";
                            pos_changed = true;
                            point_pos++;
                        }
                    }

                    if(pos_changed){
                        pos_changed = false;
                        cout << "What do you want to do with " << curr_hero->getName() << " ?" << endl;
                        cout << "Enter: Select Action" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                        for(int i = 1;i <= MarketChoices.size(); i++){
                            if(i == point_pos){
                                cout << "->";
                            }
                            else{
                                cout << "  ";
                            }

                            cout << MarketChoices[i - 1] << endl;
                        }
                    }
                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');

                assert(ch == 'b' || ch == '\n' || ch == 'q');
                if(ch == 'q') menu_pos = 0;                 //If the user pressed q he quits the menu
                else
                    if(ch == 'b') menu_pos--;               //If the user pressed b he proceed to the previous menu
                    else
                        if(ch == '\n'){                     //If the user pressed enter
                            if(point_pos == 4){             //If he pressed when he choose to show stats of hero
                                cout << "\033[2J\033[1;1H";

                                curr_hero->displayStats();

                                cout << endl << endl << "Press c to continue" << endl;

                                while((ch = getchar_silent()) != 'c'){
                                    //DO NOTHING
                                }
                            }
                            else{                         //else just proceed to next menu
                                menu_pos++;
                            }
                        }    

                cout << "\033[2J\033[1;1H";

            break;

            case 3:
                next_point_pos = 1;
                pos_changed = true;
                ch = 'c';


				do{                                         //The same prosecution as the first menu

					if(ch == 'w' && next_point_pos == 2){
						cout << "\033[2J\033[1;1H";
						pos_changed = true;
						next_point_pos--;
					}
					else{
						if(ch == 's' && next_point_pos == 1){
							cout << "\033[2J\033[1;1H";
							pos_changed = true;
							next_point_pos++;
						}
					}

					if(pos_changed){
						pos_changed = false;
						cout << "What do you want to see?" << endl;
						cout << "Enter: Select" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

						if(next_point_pos == 1){
							cout << "->Items" << endl;
							cout << "  Spells" << endl;
						}
						else{
							cout << "  Items" << endl;
							cout << "->Spells" << endl;
						}
					}
				}while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');

                assert(ch == 'b' || ch == '\n' || ch == 'q');  //If the user pressed q quits menu, b going to previous
                                                               //menu or enter proceeds to next menu
                if(ch == 'q') menu_pos = 0;
                else
                    if(ch == 'b') menu_pos--;
                    else
                        if(ch == '\n') menu_pos++;

                cout << "\033[2J\033[1;1H";        

            break;


            case 4:
                cout << "\033[2J\033[1;1H";
                pos_changed = true;
                ch = 'c';

                switch(point_pos){               //By the value of point_pos I determine if the user wants to buy
                                                 //sell or show his invetory and by the value of next_point_pos
                                                 //I determine if the user wants to do this actions at items or spells

                    case 1:                      //Chose to buy
                        if(next_point_pos == 1){    //Item

                            if(Items.empty()){                          //If the item list of the market is empty
                                cout << "\033[2J\033[1;1H";
                                cout << "Market doesn't have any Items" << endl << endl;
                                cout << endl << "Press c to continue" << endl;

                                while((ch = getchar_silent()) != 'c'){
                                    //DO NOTHING
                                }                                
                                ch = 'b';               //going to previous menu
                            }
                            else{
                                curr_item = Items.begin();  
                                do{                           //The same prosecution as the first menu with only
                                                              //difference that now I move an iterator to the items list

                                    if(ch == 'w' && curr_item != Items.begin()){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        curr_item--;
                                    }
                                    else{
                                        if(ch == 's' && curr_item != (--Items.end())){
                                            cout << "\033[2J\033[1;1H";
                                            pos_changed = true;
                                            curr_item++;
                                        }
                                    }

                                    if(pos_changed){
                                        pos_changed = false;
                                        cout << "Which Item do you want to see or buy?" << endl;
                                        cout << "Enter: Select Item" << endl << "b: Back" << endl << "q: Quit" << endl << endl;


                                        cout << left << setw(20) << "NAME" ;
                                        cout << left << setw(20) << "TYPE" ;
                                        cout << left << setw(20) << "MINIMUM LEVEL" ;
                                        cout << left << setw(20) << "PRICE" << endl ;
                                        for(list<Item*>::iterator it = Items.begin();it != Items.end();it++){
                                            if(it == curr_item){
                                                cout << "->";
                                            }
                                            else{
                                                cout << "  ";
                                            }

                                            cout << left << setw(20) << (*it)->getName() ;

                                            switch((*it)->getType()){
                                                case WEAPON:
                                                    cout << left << setw(20) << "Weapon" ;
                                                    break;
                                                case ARMOR:
                                                    cout << left << setw(20) << "Armor" ;
                                                    break;
                                                case POTION:
                                                    cout << left << setw(20) << "Potion" ;
                                                    break;
                                            }
                                            cout << left << setw(20) << (*it)->getMinLevel() ; 
                                            cout << left << setw(20) << (*it)->getValue() << endl;
                                        }
                                    }
                                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');
                            }

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;                    //The same as the other menus
                            else
                                if(ch == 'b') menu_pos--;
                                else
                                    if(ch == '\n') menu_pos++;

                            cout << "\033[2J\033[1;1H";        
                        }
                        else{                       // Chose to buy Spell
                            assert(next_point_pos == 2);

                            if(Spells.empty()){
                                cout << "\033[2J\033[1;1H";
                                cout << "Market doesn't have any spells" << endl << endl;
                                cout << endl << "Press c to continue" << endl;

                                while((ch = getchar_silent()) != 'c'){
                                    //DO NOTHING
                                }                                
                                ch = 'b'; 
                            }
                            else{
                                curr_spell = Spells.begin();
                                do{
                                    if(ch == 'w' && curr_spell != Spells.begin()){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        curr_spell--;
                                    }
                                    else{
                                        if(ch == 's' && curr_spell != (--Spells.end())){
                                            cout << "\033[2J\033[1;1H";
                                            pos_changed = true;
                                            curr_spell++;
                                        }
                                    }

                                    if(pos_changed){
                                        pos_changed = false;
                                        cout << "Which Spell do you want to see or buy?" << endl;
                                        cout << "Enter: Select Item" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                        cout << left << setw(20) << "NAME" ;
                                        cout << left << setw(20) << "TYPE" ;
                                        cout << left << setw(20) << "MINIMUM LEVEL" ;
                                        cout << left << setw(20) << "PRICE" << endl ;
                                        for(list<Spell*>::iterator it = Spells.begin();it != Spells.end();it++){
                                            if(it == curr_spell){
                                                cout << "->";
                                            }
                                            else{
                                                cout << "  ";
                                            }

                                            cout << left << setw(20) << (*it)->getName() ;

                                            switch((*it)->getSpellType()){
                                                case ICE:
                                                    cout << left << setw(20) << "IceSpell" ;
                                                    break;
                                                case FIRE:
                                                    cout << left << setw(20) << "FireSpell" ;
                                                    break;
                                                case LIGHTING:
                                                    cout << left << setw(20) << "LightingSpell" ;
                                                    break;
                                            }

                                            cout << left << setw(20) << (*it)->getMinLevel() ; 
                                            cout << left << setw(20) << (*it)->getPrice() << endl;
                                        }
                                    }
                                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');
                            }

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b') menu_pos--;
                                else
                                    if(ch == '\n') menu_pos++;     

                            cout << "\033[2J\033[1;1H";                               
                        }

                    break;

                    case 2:                      //Chose to sell
                        if(next_point_pos == 1){    //Item

                            if((curr_hero->getItems()).empty()){        //If the hero doesn't have any items at his inventory
                                cout << "\033[2J\033[1;1H";
                                cout << "You don't have any Items" << endl << endl;
                                cout << endl << "Press c to continue" << endl;

                                while((ch = getchar_silent()) != 'c'){
                                    //DO NOTHING
                                }
                                
                                ch = 'b';               //go back to previous menu
                            }
                            else{
                                curr_item = (curr_hero->getItems()).begin();

                                do{
                                    if(ch == 'w' && curr_item != (curr_hero->getItems()).begin()){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        curr_item--;
                                    }
                                    else{
                                        if(ch == 's' && curr_item != (--(curr_hero->getItems()).end())){
                                            cout << "\033[2J\033[1;1H";
                                            pos_changed = true;
                                            curr_item++;
                                        }
                                    }

                                    if(pos_changed){
                                        pos_changed = false;
                                        cout << "Which Item do you want to see or sell?" << endl;
                                        cout << "Enter: Select Item" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                        for(list<Item*>::const_iterator it = (curr_hero->getItems()).begin();it != (curr_hero->getItems()).end();it++){
                                            if(it == curr_item){
                                                cout << "->";
                                            }
                                            else{
                                                cout << "  ";
                                            }

                                            cout << (*it)->getName() << " sell price is " << (*it)->getValue() / 2 << endl;
                                        }
                                    }
                                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');
                            }

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b') menu_pos--;
                                else
                                    if(ch == '\n') menu_pos++;

                            cout << "\033[2J\033[1;1H";        
                        }
                        else{                                   //Chose to sell Spell
                            assert(next_point_pos == 2);        //The same prosecution as the previous menus

                            if((curr_hero->getSpells()).empty()){
                                cout << "\033[2J\033[1;1H";
                                cout << "You don't have any spells" << endl << endl;

                                cout << endl << "Press c to continue" << endl;

                                while((ch = getchar_silent()) != 'c'){
                                    //DO NOTHING
                                }

                                ch = 'b'; 
                            }
                            else{
                                curr_spell = (curr_hero->getSpells()).begin();

                                do{
                                    if(ch == 'w' && curr_spell != (curr_hero->getSpells()).begin()){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        curr_spell--;
                                    }
                                    else{
                                        if(ch == 's' && curr_spell != (--(curr_hero->getSpells()).end())){
                                            cout << "\033[2J\033[1;1H";
                                            pos_changed = true;
                                            curr_spell++;
                                        }
                                    }

                                    if(pos_changed){
                                        pos_changed = false;
                                        cout << "Which Spell do you want to see or sell?" << endl;
                                        cout << "Enter: Select Spell" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                        for(list<Spell*>::const_iterator it = (curr_hero->getSpells()).begin();it != (curr_hero->getSpells()).end();it++){
                                            if(it == curr_spell){
                                                cout << "->";
                                            }
                                            else{
                                                cout << "  ";
                                            }

                                            cout << (*it)->getName() << " and sell price is " << (*it)->getPrice() << endl;
                                        }
                                    }
                                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');
                            }

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b') menu_pos--;
                                else
                                    if(ch == '\n') menu_pos++;

                            cout << "\033[2J\033[1;1H";                                    
                        }
                    break;

                    case 3:                       //Chose to show inventory
                        if(next_point_pos == 1){    //Item
                            

                            if((curr_hero->getItems()).empty()){
                                cout << "\033[2J\033[1;1H";
                                cout << "You don't have any Items" << endl << endl;

                                cout << endl << "Press c to continue" << endl;

                                while((ch = getchar_silent()) != 'c'){
                                    //DO NOTHING
                                }

                                ch = 'b'; 
                            }
                            else{
                                curr_item = (curr_hero->getItems()).begin();

                                do{
                                    if(ch == 'w' && curr_item != (curr_hero->getItems()).begin()){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        curr_item--;
                                    }
                                    else{
                                        if(ch == 's' && curr_item != (--(curr_hero->getItems()).end())){
                                            cout << "\033[2J\033[1;1H";
                                            pos_changed = true;
                                            curr_item++;
                                        }
                                    }

                                    if(pos_changed){
                                        pos_changed = false;
                                        cout << "Which Item do you want to see?" << endl;
                                        cout << "Enter: Select Item" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                        for(list<Item*>::const_iterator it = (curr_hero->getItems()).begin();it != (curr_hero->getItems()).end();it++){
                                            if(it == curr_item){
                                                cout << "->";
                                            }
                                            else{
                                                cout << "  ";
                                            }

                                            cout << (*it)->getName() << endl;
                                        }
                                    }
                                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');
                            }

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b') menu_pos--;
                                else{
                                    if(ch == '\n') (*curr_item)->print();       //When the user presses enter the data of the items are printed

                                    cout << endl << endl << "Press c to continue" << endl;
                                    while((ch = getchar_silent()) != 'c'){
                                        //DO NOTHING
                                    }
                                }
                            cout << "\033[2J\033[1;1H";        
                        }
                        else{                       //Spell //The same as above at spell
                            assert(next_point_pos == 2);

                            if((curr_hero->getSpells()).empty()){
                                cout << "\033[2J\033[1;1H";
                                cout << "You don't have any Spells" << endl << endl;

                                cout << endl << "Press c to continue" << endl;

                                while((ch = getchar_silent()) != 'c'){
                                    //DO NOTHING
                                }

                                ch = 'b'; 
                            }
                            else{
                                curr_spell = (curr_hero->getSpells()).begin();

                                do{
                                    if(ch == 'w' && curr_spell != (curr_hero->getSpells()).begin()){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        curr_spell--;
                                    }
                                    else{
                                        if(ch == 's' && curr_spell != (--(curr_hero->getSpells()).end())){
                                            cout << "\033[2J\033[1;1H";
                                            pos_changed = true;
                                            curr_spell++;
                                        }
                                    }

                                    if(pos_changed){
                                        pos_changed = false;
                                        cout << "Which Spell do you want to see?" << endl;
                                        cout << "Enter: Select Item" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                        for(list<Spell*>::const_iterator it = (curr_hero->getSpells()).begin();it != (curr_hero->getSpells()).end();it++){
                                            if(it == curr_spell){
                                                cout << "->";
                                            }
                                            else{
                                                cout << "  ";
                                            }

                                            cout << (*it)->getName() << endl;
                                        }
                                    }
                                }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');                                
                            }

                            cout << "\033[2J\033[1;1H";  

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b') menu_pos--;
                                else
                                    if(ch == '\n'){
                                        (*curr_spell)->print();

                                        cout << endl << "Press c to continue" << endl;

                                        while((ch = getchar_silent()) != 'c'){
                                            //DO NOTHING
                                        }

                                        cout << "\033[2J\033[1;1H";                                               
                                    }
                        }
                    break;                        
                }

            break;

            case 5:                 //After selecting buy or Sell and after selecting to buy/sell specific item or spell
                ch = 'c';
                pos_changed = true;

                prev_point_pos = point_pos;

                switch(point_pos){
                    case 1:
                        point_pos = 1;
                        if(next_point_pos == 1){  // Chose to buy a specific Item
                            do{
                                if(ch == 'w' && point_pos > 1){             //Same menu prosecution
                                    cout << "\033[2J\033[1;1H";
                                    pos_changed = true;
                                    point_pos--;
                                }
                                else{
                                    if(ch == 's' && point_pos < 2){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        point_pos++;
                                    }
                                }

                                if(pos_changed){
                                    pos_changed = false;
                                    cout << "What do you want to do with " << (*curr_item)->getName() << " ?" << endl;
                                    cout << "Enter: Select Action" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                    for(int i = 1; i <= 2;i++){
                                        if(i == point_pos){
                                            cout << "->";
                                        }
                                        else{
                                            cout << "  ";
                                        }

                                        cout << BuyChoices[i-1] << endl;
                                    }
                                }
                            }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');

                            cout << "\033[2J\033[1;1H";

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b'){
                                    menu_pos--;
                                    point_pos = prev_point_pos;
                                }
                                else{
                                    switch(point_pos){
                                        case 1:                 //Chose to print info
                                            point_pos = prev_point_pos;
                                            (*curr_item)->print();

                                            cout << endl << "Press c to continue" << endl;

                                            while((ch = getchar_silent()) != 'c'){
                                                //DO NOTHING
                                            } 
                                            cout << "\033[2J\033[1;1H";                                             
                                        break;

                                        case 2:

                                            string temp = (*curr_item)->getName();

                                            point_pos = prev_point_pos;             //chose to buy the item
                                            if(curr_hero->getMoney() >= (*curr_item)->getValue() && curr_hero->getLevel() >= (*curr_item)->getMinLevel()){ //Checks if the hero has money and is capable enough
                                                curr_hero->Buy((list<Item*>::iterator&) curr_item);
                                                this->give((list<Item*>::iterator&) curr_item);

                                                menu_pos -= 2;
                                                cout << "You bought " << temp << endl;

                                                cout << endl << "Press c to continue" << endl;

                                                while((ch = getchar_silent()) != 'c'){
                                                    //DO NOTHING
                                                } 

                                                cout << "\033[2J\033[1;1H";                                                 
                                            }
                                            else{
                                                cout << "You don't have enougn money or you are not capable enough" << endl;

                                                cout << endl << "Press c to continue" << endl;

                                                while((ch = getchar_silent()) != 'c'){
                                                    //DO NOTHING
                                                }   

                                                cout << "\033[2J\033[1;1H";                                               
                                            }
                                        break;    
                                    }
                                }
                        }
                        else{                     //Chose to buy a specific Spell
                            assert(next_point_pos == 2);        //Same prosecution as above
                            do{
                                if(ch == 'w' && point_pos > 1){
                                    cout << "\033[2J\033[1;1H";
                                    pos_changed = true;
                                    point_pos--;
                                }
                                else{
                                    if(ch == 's' && point_pos < 2){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        point_pos++;
                                    }
                                }

                                if(pos_changed){
                                    pos_changed = false;
                                    cout << "What do you want to do with " << (*curr_spell)->getName() << " ?" << endl;
                                    cout << "Enter: Select Action" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                    for(int i = 1; i <= 2;i++){
                                        if(i == point_pos){
                                            cout << "->";
                                        }
                                        else{
                                            cout << "  ";
                                        }

                                        cout << BuyChoices[i - 1] << endl;
                                    }
                                }
                            }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');

                            cout << "\033[2J\033[1;1H";

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b'){
                                    menu_pos--;
                                    point_pos = prev_point_pos;
                                }
                                else{
                                    switch(point_pos){
                                        case 1:
                                            point_pos = prev_point_pos;
                                            (*curr_spell)->print();

                                            cout << endl << "Press c to continue" << endl;

                                            while((ch = getchar_silent()) != 'c'){
                                                //DO NOTHING
                                            }             

                                            cout << "\033[2J\033[1;1H";                                 
                                        break;

                                        case 2:
                                            point_pos = prev_point_pos;
                                            if(curr_hero->getMoney() >= (*curr_spell)->getPrice() && curr_hero->getLevel() >= (*curr_spell)->getMinLevel()){

                                                string temp = (*curr_spell)->getName();

                                                curr_hero->Buy((list<Spell*>::iterator&) curr_spell);
                                                this->give((list<Spell*>::iterator&) curr_spell);

                                                menu_pos -= 2;
                                                cout << "You bought " << temp << endl;
                                                cout << endl << "Press c to continue" << endl;

                                                while((ch = getchar_silent()) != 'c'){
                                                    //DO NOTHING
                                                }  

                                                cout << "\033[2J\033[1;1H";                                               
                                            }
                                            else{
                                                cout << "You don't have enougn money or you are not capable enough" << endl;
                                                cout << endl << "Press c to continue" << endl;

                                                while((ch = getchar_silent()) != 'c'){
                                                    //DO NOTHING
                                                } 

                                                cout << "\033[2J\033[1;1H";                                                 
                                            }
                                        break;    
                                    }
                                }                            
                           
                        }
                    break;

                    case 2:
                        point_pos = 1;
                        if(next_point_pos == 1){  //Chose to sell a specific Item //Same prosecution as above
                            do{
                                if(ch == 'w' && point_pos > 1){
                                    cout << "\033[2J\033[1;1H";
                                    pos_changed = true;
                                    point_pos--;
                                }
                                else{
                                    if(ch == 's' && point_pos < 2){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        point_pos++;
                                    }
                                }

                                if(pos_changed){
                                    pos_changed = false;
                                    cout << "What do you want to do with " << (*curr_item)->getName() << " ?" << endl;
                                    cout << "Enter: Select Action" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                    for(int i = 1; i <= 2;i++){
                                        if(i == point_pos){
                                            cout << "->";
                                        }
                                        else{
                                            cout << "  ";
                                        }

                                        cout << SellChoices[i - 1] << endl;
                                    }
                                }
                            }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');

                            cout << "\033[2J\033[1;1H";

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b'){
                                    menu_pos--;
                                    point_pos = prev_point_pos;
                                }
                                else{
                                    switch(point_pos){
                                        case 1:
                                            point_pos = prev_point_pos;
                                            (*curr_item)->print();

                                            cout << endl << "Press c to continue" << endl;

                                            while((ch = getchar_silent()) != 'c'){
                                                //DO NOTHING
                                            }  

                                            cout << "\033[2J\033[1;1H";                                           
                                        break;

                                        case 2:

                                            string temp = (*curr_item)->getName();

                                            point_pos = prev_point_pos;
                                            curr_hero->Sell((list<Item*>::iterator&) curr_item);
                                            this->get((list<Item*>::iterator&) curr_item);
                                            menu_pos -= 2;
                                            cout << "You sold " << temp << endl;

                                            cout << endl << "Press c to continue" << endl;

                                            while((ch = getchar_silent()) != 'c'){
                                                //DO NOTHING
                                            }                                    
                                            
                                            cout << "\033[2J\033[1;1H";
                                        break;    
                                    }
                                }
                        }
                        else{                     //Chose to sell a specific Spell  //Same prosecution as above
                            assert(next_point_pos == 2);
                            do{
                                if(ch == 'w' && point_pos > 1){
                                    cout << "\033[2J\033[1;1H";
                                    pos_changed = true;
                                    point_pos--;
                                }
                                else{
                                    if(ch == 's' && point_pos < 2){
                                        cout << "\033[2J\033[1;1H";
                                        pos_changed = true;
                                        point_pos++;
                                    }
                                }

                                if(pos_changed){
                                    pos_changed = false;
                                    cout << "What do you want to do with " << (*curr_spell)->getName() << " ?" << endl;
                                    cout << "Enter: Select Action" << endl << "b: Back" << endl << "q: Quit" << endl << endl;

                                    for(int i = 1; i <= 2;i++){
                                        if(i == point_pos){
                                            cout << "->";
                                        }
                                        else{
                                            cout << "  ";
                                        }

                                        cout << SellChoices[i - 1] << endl;
                                    }
                                }
                            }while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q');

                            cout << "\033[2J\033[1;1H";

                            assert(ch == 'b' || ch == '\n' || ch == 'q');
                            if(ch == 'q') menu_pos = 0;
                            else
                                if(ch == 'b'){
                                    menu_pos--;
                                    point_pos = prev_point_pos;
                                }
                                else{
                                    switch(point_pos){
                                        case 1:
                                            point_pos = prev_point_pos;
                                            (*curr_spell)->print();

                                            cout << endl << "Press c to continue" << endl;

                                            while((ch = getchar_silent()) != 'c'){
                                                //DO NOTHING
                                            }
                                            
                                            cout << "\033[2J\033[1;1H";                                             
                                        break;

                                        case 2:

                                            string temp = (*curr_spell)->getName();

                                            point_pos = prev_point_pos;
                                            
                                            curr_hero->Sell((list<Spell*>::iterator&) curr_spell);

                                            this->get((list<Spell*>::iterator&) curr_spell);

                                            menu_pos -= 2;
                                            cout << "You sold " << temp << endl;

                                            cout << endl << "Press c to continue" << endl;

                                            while((ch = getchar_silent()) != 'c'){
                                                //DO NOTHING
                                            }

                                            cout << "\033[2J\033[1;1H";                                             
                                        break;    
                                    }
                                }                            
                           
                        }
                    break;
                }
            break;    
        }
    }
}

void Grid::Square::Market::give(list<Item*>::iterator& Item){       //just delete the Item's address at the list
    Items.erase(Item);
}

void Grid::Square::Market::give(list<Spell*>::iterator& Spell){     //just delete the Spell's address at the list
    Spells.erase(Spell);
}

void Grid::Square::Market::get(std::list<Item*>::iterator& Item){   //just adds to the list the address of a specific Item 
    Items.push_back(*Item);
}

void Grid::Square::Market::get(std::list<Spell*>::iterator& Spell){ //just adds to the list the address of a specific Spell 
    Spells.push_back(*Spell);
}

Grid::Square::Market::~Market(){            //Destroying the market

    for(list<Item*>::iterator it = Items.begin(); it != Items.end();){  //Deleting Items' list
        delete *it;
        it = Items.erase(it);
    }

    for(list<Spell*>::iterator it = Spells.begin(); it != Spells.end();){   //Deleting Spells' list
        delete *it;
        it = Spells.erase(it);
    }
}