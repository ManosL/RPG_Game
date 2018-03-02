#include <cassert>
#include <vector>

#include "../Ready/Ready.hpp"
#include "../Living/Living.hpp"

const unsigned int Hero::InitialRequiredExperience = 100;


//hero constructor
Hero::Hero(const string& nam,const unsigned int& hp,const unsigned int& lvl, const unsigned int& mp ,const unsigned int& st
,const unsigned int& dext,const unsigned int&	agil,const unsigned int& def,const unsigned int& mon,const unsigned int& xp
,const unsigned int& posX,const unsigned int& posY)
: Living(nam,hp,lvl) , maxMagicPower(mp) ,currMagicPower(mp) ,strength(st) ,dexterity(dext) , 
agility(agil) , defensePoints(def),money(mon) , experience(xp),positionX(posX),positionY(posY),
first_hand(NULL),second_hand(NULL),head(NULL),body(NULL),hands(NULL),legs(NULL), RequiredExperience(InitialRequiredExperience)
{
	//cout << "A Hero created..." << endl ;
}

//every 100 experience points the hero level up
void Hero::setExperience(const unsigned int& xp)
{
	experience += xp ;

	while (experience >= RequiredExperience)
	{
		levelUp();
		experience = experience - RequiredExperience ;

		RequiredExperience += 100;
	}
}

//reduce magic to execute a spell
void Hero::reduceMagic(const int& mp)
{
	currMagicPower = currMagicPower - mp ;

	if (currMagicPower < 0 )
		currMagicPower = 0 ;

	
}

//increase magic in every round
void Hero::increaseMagic(const int& mp){

	currMagicPower += mp;

	if(currMagicPower > (signed) maxMagicPower){
		currMagicPower = maxMagicPower;
	}

	return;
}

//if the hero wants to change his armor
int Hero::changeArmor()
{
        int i = 1 ;	//show to the player all the armors of the hero with its specific number
        for(list<Item*>::iterator it = ItemList.begin() ; it != ItemList.end() ; it++)
        {
                if ( (*it)->getType() == ARMOR)
                {
                        if (i == 1)
                                cout << "Hero's Armors:" << endl << endl ;

                        cout << i << ") " << (*it)->getName() << endl ;
                        i++ ;

                }
        }
        if (i == 1)
        {        //The hero has no armors to change
                return 0 ;
        }
        else
        {		//the player picks the number of the armor he wants to put on the hero
                int num = 0;
        		while(num < 1 || num > i){
        			cout << "Choose the number of armor you want to equip:        " ;
                	cin >> num ;

					cin.clear();
					cin.ignore(500,'\n');
				}               


                i = 1 ;	//search the list for this armor
                for (list<Item*>::iterator it = ItemList.begin() ; it != ItemList.end() ; it++)
                {
                        if ( (*it)->getType() == ARMOR)
                        {        if (i == num)
                                {
                                        this->Equip(it);	//equip the wanted armor
                                        return 1;
                                }
                                i++ ;
                        }
                }
                return 1;

        }
}

//if the hero wants to change his weapon
int  Hero::changeWeapon()
{

		int i = 1 ;	//show to the player all the weapons of the hero with its specific number
        for(list<Item*>::iterator it = ItemList.begin() ; it != ItemList.end() ; it++)
        {
                if ( (*it)->getType() == WEAPON)
                {
                        if (i == 1)
                                cout << "Hero's Weapons:" << endl << endl ;

                        cout << i << ") " << (*it)->getName() << endl ;
                        i++ ;

                }
        }
        if (i == 1)
        {        //The hero has no weapons to change;
                return 0 ;
        }
        else
        {		//the player picks the number of the weapon he wants to put on the hero
               int num = 0;
        		while(num < 1 || num > i){
        			cout << "Choose the number of weapon you want to equip:        " ;
                	cin >> num ;

					cin.clear();
					cin.ignore(500,'\n');
				}               
              
                i = 1 ;
                for (list<Item*>::iterator it = ItemList.begin() ; it != ItemList.end() ; it++)
                {
                        if ( (*it)->getType() == WEAPON )
                        {        if (i == num)
                                {
                                        this->Equip(it);//equip the wanted weapon
                                        return 1;
                                }
                                i++ ;
                        }
                }
                return 1;

        }

}

list<Item*>::iterator Hero::choosePotion()
{
        int i = 1;//show the player all he potions of the hero with specific number
        for (list<Item*>::iterator it = ItemList.begin() ; it != ItemList.end() ; it++)
        {
                if ( (*it)->getType() == POTION)
                {
                        if (i == 1 )
                                cout << "Hero's Potions: " << endl << endl ;
                        cout << i << ") " << (*it)->getName() << endl ; 
                        i++ ;
                }
        }

        if (i == 1)
        {
                //The hero has no Potions ;
                list<Item*>::iterator k = ItemList.end();
                return k ;
        }
        else
        {      	int num = 0;
        		while(num < 1 || num > i){
        			cout << "Choose the number of the potion you want: " ;
                	cin >> num ;

					cin.clear();
					cin.ignore(500,'\n');
				}

                    
                i = 1;	//search the list to find the wanted potion
                for (list<Item*>::iterator it = ItemList.begin() ; it !=ItemList.end() ; it++)
                {
                        if ( (*it)->getType() == POTION)
                        {        if (num == i)
                                        return it ; //return the potion
                                i++;
                        }
                }
        }

        list<Item*>::iterator it = ItemList.begin() ;
        return it ;

}

void Hero::Attack(Monster& Target)
{
	double MonsterDodge = Target.getDodgePossibility() ;

	double posDodge = (double)rand()/(double)(RAND_MAX) ;

	//check if the monster avoided the attack 
 	if ( posDodge < MonsterDodge )
 	{	cout << "The monster avoided the attack..." << endl ;
 		return ;
 	}
 	else
 	{	int damage ;
 		int dmg ;
 		if (first_hand != NULL)//if the hero has one hand with weapon
 		{			
 			damage =  this->getStrength() ; //take the strenth
 				
 			dmg =  (damage * damage)/(damage + Target.getArmor() ); //attack formula 

 			Target.reduceHealth(dmg); //reduce the monster's health

 			if (first_hand->isOneHanded() == false) //if the weapon is two-handed return
 				return ;
 			
 		}

 		if ( second_hand != NULL) //the hero holds 2 one-handed weapons 
 		{
 			damage = this->getStrength() ;
 			
 			dmg =  (damage * damage)/(damage + Target.getArmor() );
 
 			Target.reduceHealth(dmg);

 			if (second_hand->isOneHanded() == false)
 				return ;
 		}

		if(first_hand == NULL && second_hand == NULL){ //if the hero dont hold any weapon

			damage = this->getStrength();

 			dmg =  (damage * damage)/(damage + Target.getArmor() );

 			Target.reduceHealth(dmg);

			return; 			
		}

 	}

}

//choose which spell to execute
list<Spell*>::iterator Hero::chooseSpell()
{
        int i = 1 ;
        int num = 0 ;

        //show all the spells of the hero with specific number to the player
        for(list<Spell*>::iterator it = SpellList.begin() ; it != SpellList.end() ; it++)
        {
                if (i == 1)
                cout << "Hero's Spells:" << endl << endl ;
                cout << i << ")        " << (*it)->getName() << endl ;
                i++ ;
        }

        if (i == 1)
        {
                cout << "The hero has no spells" << endl << endl ;
        }
        else
        {       //the player showed which spell wants to execute his hero
			while(num < 1 || num > i){
        		cout << "Choose the number of the spell you want: " ;

                cin >> num ;

				cin.clear();
				cin.ignore(500,'\n');
			}

            i = 1;	//search for the wanted spell

            for (list<Spell*>::iterator it = SpellList.begin() ; it !=SpellList.end() ; it++)
            {
                    if (num == i)
                    	return it ;	//return the spell
                i++;
            }
        }
        
        list<Spell*>::iterator it = SpellList.begin();
        return it ;
}


int  Hero::castSpell(Monster& mon)
{
        if ( SpellList.size() == 0)
        {
                //the hero doesn't have spells
                return 0 ;
        }

        list<Spell*>::iterator attackSpell = this->chooseSpell(); // choose the spell

        //search for that spell in the list
        for ( list<Spell*>::iterator it = SpellList.begin() ; it != SpellList.end() ; it++)
        {
                if (it == attackSpell)
                {
                    int SpellMag = (*attackSpell)->getMagic() ;
                    int HeroMag  = this->getMagic();

                    if (HeroMag > SpellMag)	//execute the spell only if the hero has the required magic power
                    {        this->reduceMagic(SpellMag) ; 	//reduce the magic of the hero

                            (*it)->useSpell(mon, this->getDexterity() ); //use the spell
                    }
                    else
                    {
							//The hero has not enough magic power to execute the Spell
                    		return -1;
                    }

                    //delete *it;	//delete the spell
                    it = SpellList.erase(it);

                    break ; //break the loop
                }
        }


        return 1 ; //successful return

}

void Hero::Move(const Direction& dir)   //I determined in the grid if the hero can move in that direction
{										//Just changes properly the position of hero
	switch(dir){
		case UP:
			positionY--;
			break;
		case DOWN:
			positionY++;
			break;
		case LEFT:
			positionX--;
			break;
		case RIGHT:
			positionX++;
			break;
	}
}

void Hero::Equip(list<Item*>::iterator& item){

	const ItemType curr_type = (*item)->getType();  //Determine what Item is (armor,potion or weapon)
	
	switch(curr_type){
		case WEAPON:							//If the item is Weapon
		{	int choice;
			Weapon* weapon = (Weapon*) *item;

			if(weapon->isOneHanded()){			//If it is one hand weapon
				if(first_hand != NULL && second_hand != NULL){		//I find if there is a hand available to put it
					
					if(first_hand == second_hand){				//If the hero holds a two handed weapon will be replaced

						strength -= first_hand->getDamage(); 

						ItemList.push_back((Item*) first_hand);

						first_hand = weapon;

						strength += first_hand->getDamage();

						second_hand = NULL;

						cout << (*item)->getName() << " equipped" << endl;
						ItemList.erase(item);

						return;
					}
					else{				//If he holds two one hand weapons(one on each hand) I ask him with which hand wants to change
						cout << "Do you want to replace it with the weapon at first hand, second hand or with nothing?(f,s or n)" << endl;
						choice = getchar_silent();

						switch(choice){
							case 'f':
								strength -= first_hand->getDamage();

								ItemList.push_back((Item*) first_hand);

								first_hand = weapon;

								strength += first_hand->getDamage();

								cout << (*item)->getName() << " equipped" << endl;
								ItemList.erase(item);

								break;
							case 's':
								strength -= second_hand->getDamage();

								ItemList.push_back((Item*) second_hand);

								second_hand = weapon;

								strength += second_hand->getDamage();

								cout << (*item)->getName() << " eqipped" << endl;
								ItemList.erase(item);

								break;
							case 'n':
								break;
						}
					}

					return;
				}
				else{					//Else I find an available hand
					if(first_hand == NULL){
						first_hand = weapon;

						strength += weapon->getDamage();

						cout << (*item)->getName() << " equipped" << endl;

						ItemList.erase(item);
						return;
					}
					else
						if(second_hand == NULL){
							second_hand = weapon;

							strength += weapon->getDamage();

							cout << (*item)->getName() << " equipped" << endl;
							ItemList.erase(item);
						}
				}
			}
			else{			//If the weapon that will be equipped is two hand

				if(first_hand == NULL && second_hand == NULL){		//Check if both hands are free

					first_hand = second_hand = weapon;

					strength += weapon->getDamage();

					cout << (*item)->getName() << " equipped" << endl;
					ItemList.erase(item);

					return;
				}
				else{									//else
					if(first_hand == second_hand){		//Checking if the hero holds a two hand weapon already and I will replace it

						strength -= first_hand->getDamage();

						ItemList.push_back((Item*) first_hand);

						first_hand = second_hand = weapon;

						strength += weapon->getDamage();

						cout << (*item)->getName() << " equipped" << endl;

						ItemList.erase(item);

						return;
					}
					else{						//else if hero holds somewhere a one hand weapon I replace it
						if(first_hand != NULL){		
							strength -= first_hand->getDamage();

							ItemList.push_back((Item*) first_hand);

							first_hand = NULL;
						}

						if(second_hand != NULL){
							strength -= second_hand->getDamage();

							ItemList.push_back((Item*) second_hand);

							second_hand = NULL;
						}

						first_hand = second_hand = weapon;

						strength += weapon->getDamage();

						cout << (*item)->getName() << " equipped" << endl;

						ItemList.erase(item);

						return;
					}
				}
			}

			break;
		}	
		case ARMOR:					//In case the item is armor
		{
			Armor* armor = (Armor*) *item;
			const body_part part = armor->getAppliedPart();		//I determine in which body part applies

			switch(part){		//the only thing that I do in each case is to check if the hero wears already something and I will replace it
				case HEAD:
					if(head != NULL){
						defensePoints -= armor->getDefensePoints();

						ItemList.push_back((Item*) head);
					}

					head = armor;
					defensePoints += head->getDefensePoints();

					cout << (*item)->getName() << " equipped" << endl;

					ItemList.erase(item);

					break; 
				case BODY:
					if(body != NULL){
						defensePoints -= armor->getDefensePoints(); 

						ItemList.push_back((Item*) body);
					}

					body = armor;
					defensePoints += body->getDefensePoints();

					cout << (*item)->getName() << " equipped" << endl;

					ItemList.erase(item);

					break; 				
				case HANDS:
					if(hands != NULL){
						defensePoints -= armor->getDefensePoints();

						ItemList.push_back((Item*) hands);
					}

					hands = armor;
					defensePoints += hands->getDefensePoints();

					cout << (*item)->getName() << " equipped" << endl;

					ItemList.erase(item);

					break; 				
				case LEGS:
					if(legs != NULL){
						defensePoints -= armor->getDefensePoints();

						ItemList.push_back((Item*) legs);
					}

					legs = armor;
					defensePoints += legs->getDefensePoints();

					cout << (*item)->getName() << " equipped" << endl;

					ItemList.erase(item);

					break; 				
			}

			break;
		}

		default:
			cout << "Something went wrong" << endl;
			break;
	}

	return;
}

//function to use the potion
void Hero::UsePotion(list<Item*>::iterator& item)
{
	if((*item)->getType() != POTION){
		cout << "Cannot use Armor or Weapon like this." << endl;
		return;
	}

	Potion* potion = (Potion*) *item;

	switch(potion->getIncreasedStatistic()){		//Determine what statistic the potion increases and I increase it
		case HEALTH:
			Living::increaseHealth(potion->getIncreasedValue());
			break;
		case MAGIC:
			increaseMagic(potion->getIncreasedValue());
			break;
		case STRENGTH:
			setStrength(getStrength() + potion->getIncreasedValue());
			break;
		case DEXTERITY:
			setDexterity(getDexterity() + potion->getIncreasedValue());
			break;
		case AGILITY:
			setAgility(getAgility() + potion->getIncreasedValue());
			break;
	}

	delete *item; //delete the potion

	ItemList.erase(item);

	return;
}

void Hero::CheckInventory()   //The menu has the same prosecution as the market menu
{
	string temp;
	list<Item*>::iterator curr_item;
	list<Spell*>::iterator curr_spell;
	int menu_pos = 1;
	int point_pos = 1, next_point_pos;
	int ch = 'c';
	bool pos_changed = true;

	while(menu_pos){
		assert(menu_pos > 0 && menu_pos < 4);

		switch(menu_pos){
			case 1:						//The user choose to view it's items or spells
				pos_changed = true;
				point_pos = 1;
				
				do{

					if(ch == 'w' && point_pos == 2){
						cout << "\033[2J\033[1;1H";
						pos_changed = true;
						point_pos--;
					}
					else{
						if(ch == 's' && point_pos == 1){
							cout << "\033[2J\033[1;1H";
							pos_changed = true;
							point_pos++;
						}
					}

					if(pos_changed){
						pos_changed = false;
						cout << "What do you want to see?" << endl;
						cout << "Enter: Select" << endl << "b: Back" << endl << "i: Show Hero Info" << endl << "q: Quit" << endl << endl;
						if(point_pos == 1){
							cout << "->Items" << endl;
							cout << "  Spells" << endl;
						}
						else{
							cout << "  Items" << endl;
							cout << "->Spells" << endl;
						}
					}
				}while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q' && ch != 'i');

				
				assert(ch == 'b' || ch == '\n' || ch == 'q' || ch == 'i');
				if(ch == 'b' || ch == 'q') menu_pos--;
				else
					if(ch == '\n'){
						cout << "\033[2J\033[1;1H";
						menu_pos++;
					}
					else
						if(ch == 'i'){
							cout << "\033[2J\033[1;1H";
							displayStats();

							cout << endl << endl << "Press c to continue" << endl;

							while((ch = getchar_silent()) != 'c'){
								//DO NOTHING
							}

							cout << "\033[2J\033[1;1H";
							
						}				
			
			break;

			case 2:							//The user chooses which item or spell he wants to see

				pos_changed = true;
				ch = 'c';

				if(point_pos == 1){
					
					if(ItemList.empty()){
						cout << "\033[2J\033[1;1H";
						cout << "You don't have any Items in your Inventory" << endl << endl << endl;

						cout << "Press c to continue" << endl << endl << endl;

						while((ch = getchar_silent()) != 'c'){
							//DO NOTHING
						}

						ch = 'b'; //Because I will go to previous menu
					}
					else{
						curr_item = ItemList.begin();

						do{

							if(ch == 'w' && curr_item != ItemList.begin()){
								cout << "\033[2J\033[1;1H";
								pos_changed = true;								
								curr_item--;
							}
							else{
								if(ch == 's' && curr_item != (--ItemList.end())){
									cout << "\033[2J\033[1;1H";
									pos_changed = true;									
									curr_item++;
								}
							}

							if(pos_changed){
								pos_changed = false;
								cout << "These are the Items that you have in your inventory" << endl;
								cout << "Enter: Select Item" << endl << "b: Back" << endl << "i: Show hero Info" << endl << "q: Quit" << endl << endl;
								for(list<Item*>::iterator it = ItemList.begin(); it != ItemList.end(); it++){
									if(it == curr_item){
										cout << "->";
									}
									else{
										cout << "  ";
									}

									cout << (*it)->getName() << " is a ";

									switch((*it)->getType()){
										case WEAPON:
											cout << "Weapon" << endl;
											break;
										case ARMOR:
											cout << "Armor" << endl;
											break;
										case POTION:
											cout << "Potion" << endl;
											break;
									}
								}
							}	
						}while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q' && ch != 'i');
					}

					assert(ch == 'b' || ch == '\n' || ch == 'q' || ch == 'i');
					if(ch == 'q') menu_pos = 0;
					else
						if(ch == 'b'){
							cout << "\033[2J\033[1;1H";
							menu_pos--;
						}
						else if(ch == '\n') { 
							cout << "\033[2J\033[1;1H"; menu_pos++;
						}
						else
						if(ch == 'i'){
							cout << "\033[2J\033[1;1H";
							displayStats();

							cout << endl << endl << "Press c to continue" << endl;

							while((ch = getchar_silent()) != 'c'){
								//DO NOTHING
							}

							cout << "\033[2J\033[1;1H";
						}						
				}
				else{
					assert(point_pos == 2);

					if(SpellList.empty()){
						cout << "\033[2J\033[1;1H";
						cout << "You don't have any Spells in your Inventory" << endl << endl << endl;

						cout << "Press c to continue " << endl << endl << endl;

						while((ch = getchar_silent()) != 'c'){
							//DO NOTHING
						}

						ch = 'b'; //Because I will go to previous menu
					}
					else{
						curr_spell = SpellList.begin();

						do{

							if(ch == 'w' && curr_spell != SpellList.begin()){
								cout << "\033[2J\033[1;1H";
								pos_changed = true;
								curr_item--;
							}
							else{
								if(ch == 's' && curr_spell != (--SpellList.end())){
									cout << "\033[2J\033[1;1H";
									pos_changed = true;
									curr_spell++;
								}
							}

							if(pos_changed){
								pos_changed = false;
								cout << "These are the Spells that you have in your inventory" << endl;
								cout << "Enter: Select Spell" << endl << "b: Back" << endl <<"i: Show Hero Info" << endl << "q: Quit" << endl << endl;
								for(list<Spell*>::iterator it = SpellList.begin(); it != SpellList.end(); it++){
									if(it == curr_spell){
										cout << "->";
									}
									else{
										cout << "  ";
									}

									cout << (*it)->getName() << " is a ";

									switch((*it)->getSpellType()){
										case ICE:
											cout << "Ice Spell" << endl;
											break;
										case FIRE:
											cout << "Fire Spell" << endl;
											break;
										case LIGHTING:
											cout << "Lighting Spell" << endl;
											break;
									}
								}
							}	
						}while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q' && ch != 'i');
					}

					assert(ch == 'b' || ch == '\n' || ch == 'q' || ch == 'i');
					if(ch == 'q') menu_pos = 0;
					else
						if(ch == 'b'){
							cout << "\033[2J\033[1;1H"; 
							menu_pos--;
						}
						else if(ch == '\n'){
							cout << "\033[2J\033[1;1H";
							menu_pos++;
						}
						else
						if(ch == 'i'){
							cout << "\033[2J\033[1;1H";
							displayStats();

							cout << endl << endl << "Press c to continue" << endl;

							while((ch = getchar_silent()) != 'c'){
								//DO NOTHING
							}

							cout << "\033[2J\033[1;1H";
						}											
				}	
			

			break;

			case 3:			//The user chooses to drop the item he chose or to equip the item if it is weapon or armor
							//or to use the item if he chose a potion

				pos_changed = true;
				vector<string> WeaponOrArmorChoices;
				vector<string> PotionChoices;
				vector<string> SpellChoices; 
				ch = 'c';
				next_point_pos = 1;

				WeaponOrArmorChoices.push_back("Show Info");
				WeaponOrArmorChoices.push_back("Equip");
				WeaponOrArmorChoices.push_back("Drop");

				PotionChoices.push_back("Show Info");
				PotionChoices.push_back("Use");
				PotionChoices.push_back("Drop");

				SpellChoices.push_back("Show Info");
				SpellChoices.push_back("Drop");

				if(point_pos == 1){			//If I chose Item
					if((*curr_item)->getType() == POTION){
						next_point_pos = 1;

						do{

							if(ch == 'w' && next_point_pos > 1){
								cout << "\033[2J\033[1;1H";
								pos_changed = true;
								next_point_pos--;
							}
							else{
								if( ch == 's' && next_point_pos < 3){
									cout << "\033[2J\033[1;1H";
									pos_changed = true;
									next_point_pos++;
								}
							}

							if(pos_changed){
								pos_changed = false;
								cout << "What do you want to do with the potion?" << endl;
								cout << "Enter: Select Action" << endl << "b: Back" << endl << "i: Show Hero Info" << endl << "q: Quit" << endl << endl;

								for(int i = 1; i <= 3; i++){
									if(i == next_point_pos){
										cout << "->";
									}
									else{
										cout << "  ";
									}

									cout << PotionChoices[i - 1] << endl;
								}
							}
						}while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q' && ch != 'i');

						assert(ch == 'b' || ch == '\n' || ch == 'q' || ch == 'i');

						if(ch == 'q'){
							cout << "\033[2J\033[1;1H";
							menu_pos = 0;
						}
						else
						if(ch == 'b'){
							cout << "\033[2J\033[1;1H";
							menu_pos--;
						}
						else
						if(ch == 'i'){
							cout << "\033[2J\033[1;1H";
							displayStats();

							cout << endl << endl << "Press c to continue" << endl;

							while((ch = getchar_silent()) != 'c'){
								//DO NOTHING
							}

							cout << "\033[2J\033[1;1H";
						}						
						else{
							assert(next_point_pos > 0 && next_point_pos < 4);

							switch(next_point_pos){
								case 1:
									cout << "\033[2J\033[1;1H";
									(*curr_item)->print();

									cout << endl << endl << "Press c to continue" << endl;
									while((ch = getchar_silent()) != 'c'){
										//DO NOTHING
									}

									cout << "\033[2J\033[1;1H";
									break;
								case 2:
									cout << "\033[2J\033[1;1H";
									this->UsePotion(curr_item);
									menu_pos = menu_pos - 2;
									break;
								case 3:
									cout << "\033[2J\033[1;1H";
									this->Drop(curr_item);
									menu_pos = menu_pos - 2;
									break;	
							}
						}
					}	
					else{
						next_point_pos = 1;

						do{

							if(ch == 'w' && next_point_pos > 1){
								cout << "\033[2J\033[1;1H";
								pos_changed = true;
								next_point_pos--;
							}
							else{
								if( ch == 's' && next_point_pos < 3){
									cout << "\033[2J\033[1;1H";
									pos_changed = true;
									next_point_pos++;
								}
							}

							if(pos_changed){
								pos_changed = false;
								cout << "What do you want to do with this Armor or Weapon?" << endl;
								cout << "Enter: Select Action" << endl << "b: Back" << endl << "i: Show Hero Info" << endl << "q: Quit" << endl << endl;

								for(int i = 1; i <= 3; i++){
									if(i == next_point_pos){
										cout << "->";
									}
									else{
										cout << "  ";
									}

									cout << WeaponOrArmorChoices[i - 1] << endl;
								}
							}
						}while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q' && ch != 'i');

						assert(ch == 'b' || ch == '\n' || ch == 'q' || ch == 'i');
						if(ch == 'q') menu_pos = 0;
						else
						if(ch == 'b'){
							cout << "\033[2J\033[1;1H";
							menu_pos--;
						}
						else
						if(ch == 'i'){
							cout << "\033[2J\033[1;1H";
							displayStats();

							cout << endl << endl << "Press c to continue" << endl;

							while((ch = getchar_silent()) != 'c'){
								//DO NOTHING
							}

							cout << "\033[2J\033[1;1H";
						}						
						else{
							assert(next_point_pos > 0 && next_point_pos < 4);
							switch(next_point_pos){
								case 1:
									cout << "\033[2J\033[1;1H";
									(*curr_item)->print();
									
									cout << endl << endl << "Press c to continue" << endl;
									while((ch = getchar_silent()) != 'c'){
										//DO NOTHING
									}

									cout << "\033[2J\033[1;1H";
									break;
								case 2:
									cout << "\033[2J\033[1;1H";
									this->Equip(curr_item);
									menu_pos = menu_pos - 2;
									break;
								case 3:
									cout << "\033[2J\033[1;1H";
									this->Drop(curr_item);
									menu_pos = menu_pos - 2;
									break;	
							}
						}
					}				
				}	
				else{						//If I chose Spell
					assert(point_pos == 2);

					next_point_pos = 1;

					do{

						if(ch == 'w' && next_point_pos != 1){
							cout << "\033[2J\033[1;1H";
							pos_changed = true;
							next_point_pos--;
						}
						else{
							if(ch == 's' && next_point_pos != 2){
								cout << "\033[2J\033[1;1H";
								pos_changed = true;
								next_point_pos++;
							}
						}

						if(pos_changed){
							pos_changed = false;
							cout << "What do you want to do with this spell?" << endl;
							cout << "Enter: Select Action" << endl << "b: Back" << endl << "i: Show Hero Info" << endl << "q: Quit" << endl << endl;

							for(int i = 1;i <= 2;i++){
								if(next_point_pos == i){
									cout << "->";
								}
								else{
									cout << "  ";
								}

								cout << SpellChoices[i - 1] << endl;
							}
						}
					}while((ch = getchar_silent()) != 'b' && ch != '\n' && ch != 'q' && ch != 'i');

					assert(ch == 'b' || ch == '\n' || ch == 'q' || ch == 'i');
					if(ch == 'q') menu_pos = 0;
					else
					if(ch == 'b'){
						cout << "\033[2J\033[1;1H";
						menu_pos--;
					}
					else
					if(ch == 'i'){
						cout << "\033[2J\033[1;1H";
						displayStats();

						cout << endl << endl << "Press c to continue" << endl;

						while((ch = getchar_silent()) != 'c'){
							//DO NOTHING
						}

						cout << "\033[2J\033[1;1H";
					}					
					else{
						assert(next_point_pos > 0 && next_point_pos < 3);
						switch(next_point_pos){
							case 1:
								cout << "\033[2J\033[1;1H";
								(*curr_spell)->print();

								cout << endl << endl << "Press c to continue" << endl;
								while((ch = getchar_silent()) != 'c'){
									//DO NOTHING
								}
								menu_pos = menu_pos - 2;

								cout << "\033[2J\033[1;1H";
								break;
							case 2:
								cout << "\033[2J\033[1;1H";
								this->Drop(curr_spell);
								menu_pos = menu_pos - 2;
							break;
						}
					}
				}			
			

			break;
		}
	}

	return;
}

void Hero::Drop(std::list<Item*>::iterator& item){ //Deletes the item and erase it from list
	delete *item;
	ItemList.erase(item);

	return;
}

void Hero::Drop(std::list<Spell*>::iterator& spell){ //Deletes the spell and erase it from list
	delete *spell;
	SpellList.erase(spell);

	return;
}

void Hero::Buy(list<Item*>::iterator& BoughtItem){ //Just decrease money and push back the address of the item to the list
	money -= (*BoughtItem)->getValue();
	ItemList.push_back(*BoughtItem);
}

void Hero::Buy(list<Spell*>::iterator& BoughtSpell){ //Just decrease money and push back the address of the spell to the list
	money -= (*BoughtSpell)->getPrice();
	SpellList.push_back(*BoughtSpell);
}

void Hero::Sell(std::list<Item*>::iterator& Item){  //Just increases money and deleting from the list the address of the item 

	money += ((*Item)->getValue()) / 2;
	ItemList.erase(Item);
}

void Hero::Sell(std::list<Spell*>::iterator& Spell){  //Just increases money and deleting from the list the address of the item 

	money += ((*Spell)->getPrice()) / 2;
	SpellList.erase(Spell);
}

//function to pick which option wants the player to do in each round with each hero
int Hero::pickAttack()
{
	cout << endl << "Hero" << " : " << this->getName() << endl ;
	cout <<"Choose Attack with enter(up-down with w-s ):"<< endl ;
	cout << "->	Attack" << endl ;
	cout << "	Use Spell" << endl ;
    cout << "	Use Potion" << endl ;
    cout << "	Change Weapon" << endl;
    cout << "	Change Armor" << endl;
	cout << "	Show Hero Info" << endl;
    char ch ;
    int pos = 1 ;
   	ch = 'c';

    while ( (ch = getchar_silent())  != '\n')
    {		cout << "\033[2J\033[1;1H";

			cout << endl << "Hero" << " : " << this->getName() << endl ;

    		cout <<"Choose Attack with enter(up-down with w-s):"<< endl ;
    		if (ch == 's')
    		{
    			if (pos < 6)	//corner case
    				pos++;
    			else if (pos == 6)
    				pos = 1;
    		}
    		if (ch == 'w')	//corner case
    		{
    			if (pos > 1)
    				pos-- ;
    			else if (pos == 1)
    				pos = 6 ;
    		}
    		int k = 1; 
    		if (k == pos)
    			cout <<"->" ;
    		cout << "	Attack"  << endl ;
    		
    		k = 2;
    		if (k == pos)
    			cout << "->" ;
			cout << "	Use Spell" << endl ;
			
			k = 3;
    		if (k == pos)
    			cout << "->";
    		cout << "	Use Potion" << endl ;

    		k = 4;
    		if (k == pos)
    			cout << "->";
    		cout << "	Change Weapon" << endl;

    		k = 5 ;
    		if (k == pos)
    			cout << "->";
    		cout << "	Change Armor" << endl;

			k = 6;
			if(k == pos)
				cout << "->";
			cout << "	Show Hero Info" << endl;	
    }
    return pos;
}

//function to pick which monster you want to attack
int Hero::pickMonster(const Monster**& ptrMonsters ,const unsigned int& numMonsters)
{
	int num = 0;
	
	while(num < 1 || num > numMonsters){
		cout << "\033[2J\033[1;1H";

		cout << "Alive Monsters:" << endl ;
		for (unsigned int i = 0 ; i < numMonsters ; i++)
		{	//show the alive monsters
			if (ptrMonsters[i]->getHealth() > 0)
				cout << i+1 << ")  " << ptrMonsters[i]->getName() << endl ;
		}

		cout << "Press the number of the monster you want to attack or cast a spell:  "  ;
		cin	>> num ;//pick the number of the monster you want

		cin.clear();
		cin.ignore(500,'\n');
	}

	return num - 1 ; 
}

Hero::~Hero()		//Destroying the hero
{
	if(head != NULL)  delete head;			//Deleting what hero wears
	if(body != NULL)  delete body;
	if(hands != NULL) delete hands;
	if(legs != NULL)  delete legs;
 
	if(first_hand == second_hand && first_hand != NULL){  //Deleting what hero holds

		assert(second_hand != NULL && !first_hand->isOneHanded());
		delete first_hand;
	}
	else{
		if(first_hand != NULL)  delete first_hand;
		if(second_hand != NULL) delete second_hand;
	}

	for(list<Spell*>::iterator it = SpellList.begin(); it != SpellList.end();){ //Deleting it's item list
		delete *it;
		it = SpellList.erase(it);
	}

	for(list<Item*>::iterator it = ItemList.begin(); it != ItemList.end();){   //Deleting it's spell list
		delete *it;
		it = ItemList.erase(it);
	}
	//cout << "A Hero destroyed..." << endl ;
}

Warrior::Warrior(const string& nam,const int& hp,const unsigned int& lvl, const int& mp ,const int& st
,const int& dext,const int&	agil,const int& def,const unsigned int& mon,const unsigned int& xp
,const unsigned int& posX,const unsigned int& posY)
: Hero(nam,hp,lvl,mp,st,dext,agil,def,mon,xp,posX,posY)
{
	//cout << "A Warrior created..." << endl;
}

void Warrior::levelUp()		//Leveling up the warrior
{	
	
	int stren = Hero::getStrength();
	int agil  = Hero::getAgility();
	int dext  = Hero::getDexterity();

	unsigned int max_hp = Living::getMaxHealth();	//take the statistics
	unsigned int max_mp = Hero::getMaxMagic();

	int cur_hp = Living::getHealth();
	int cur_mp = Hero::getMagic();

	cur_hp = cur_hp + cur_hp * 0.15 ;
	cur_mp = cur_mp + cur_mp * 0.15 ;

	max_hp = max_hp + max_hp * 0.25 ;		//increase the statistics
	max_mp = max_mp + max_mp * 0.25 ;

	stren = stren + stren * 0.5 ;
	agil  = agil  + agil  * 0.5 ;
	dext  = dext  + dext  * 0.25 ;

	Hero::setStrength(stren);
	Hero::setAgility(agil);
	Hero::setDexterity(dext);

	Hero::setCurrentMagic(cur_mp);		//replace the statistics
	Living::setCurrentHealth(cur_hp);

	Hero::setMaxMagic(max_mp);
	Living::setMaxHealth(max_hp);

	Living::setLevel();

}

void Warrior::displayStats(void)		//Showing Info about warrior
{
	cout << "---------------------------------------------" << endl ;
	cout << "Hero Statistics:"	<< endl ;
	cout << "Warrior Name:	"	<< Living::getName()	<< endl ;
	cout << "Level:		" 		<< Living::getLevel()	<< endl ;
	cout << "Health Power:	"	<< Living::getHealth()	<< "/" << Living::getMaxHealth() << endl ;
	cout << "Magic Power:	"	<< Hero::getMagic()		<< "/" << Hero::getMaxMagic() << endl	;
	cout << "Strength:	"		<< Hero::getStrength()	<< endl ;
	cout << "Defense Points: "  << Hero::getDefensePoints() << endl; 
	cout << "Dexterity:	"		<< Hero::getDexterity()	<< endl	;
	cout << "Agility:	"		<< Hero::getAgility()	<< endl ;
	cout << "Money:		"		<< Hero::getMoney()		<< endl ;
	cout << "Experience:	"	<< Hero::getExperience()<< "/" << Hero::getRequiredExperience() << endl ;
	cout << "---------------------------------------------" << endl << endl ;

	cout << endl << "Hero holds: " << endl;
	if(Hero::getFirstHand() == Hero::getSecondHand() && Hero::getFirstHand() != NULL){
		cout << "Two handed: " << Hero::getFirstHand()->getName() << endl;
	}
	else{
		if(Hero::getFirstHand() != NULL){
			cout << "First hand: " << Hero::getFirstHand()->getName() << endl;
		}

		if(Hero::getSecondHand() != NULL){
			cout << "Second hand: " << Hero::getSecondHand()->getName() << endl;
		}

		if(Hero::getFirstHand() == NULL && Hero::getSecondHand() == NULL){
			cout << "Hero doesn't hold any weapons." << endl;
		}
	}
	cout << "---------------------------------------------" << endl << endl ;

	cout << "Hero wears:" << endl;
	if(Hero::getHeadArmor() != NULL){
		cout << "Head Armor: " << Hero::getHeadArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any head armor" << endl;
	}
	
	if(Hero::getBodyArmor() != NULL){
		cout << "Body Armor: " << Hero::getBodyArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any body armor" << endl;
	}
	if(Hero::getHandsArmor() != NULL){
		cout << "Hand Armor: " << Hero::getHandsArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any hand armor" << endl;
	}	

	if(Hero::getLegsArmor() != NULL){
		cout << "Leg Armor: " << Hero::getLegsArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any leg armor" << endl;
	}

	cout << "---------------------------------------------" << endl << endl ;		
}

Warrior::~Warrior(void)
{
	//cout << "A Warrior destroyed..." << endl ;
}

Sorcerer::Sorcerer(const string& nam,const int& hp,const unsigned int& lvl, const int& mp ,const int& st
,const int& dext,const int&	agil,const int& def,const unsigned int& mon,const unsigned int& xp,
const unsigned int& posX,const unsigned int& posY)
: Hero(nam,hp,lvl,mp,st,dext,agil,def,mon,xp,posX,posY)
{
	//cout << "A Sorcerer created..." << endl;
}

void Sorcerer::displayStats(void) //showing info about the sorcerer
{
	cout << "---------------------------------------------" << endl ;
	cout << "Hero Statistics:"	<< endl ;
	cout << "Sorcerer Name:	"	<< Living::getName()	<< endl ;
	cout << "Level:		" 		<< Living::getLevel()	<< endl ;
	cout << "Health Power:	"	<< Living::getHealth()	<< "/" << Living::getMaxHealth() << endl ;
	cout << "Magic Power:	"	<< Hero::getMagic()		<< "/" << Hero::getMaxMagic() << endl	;
	cout << "Strength:	"		<< Hero::getStrength()	<< endl ;
	cout << "Defense Points: "  << Hero::getDefensePoints() << endl; 
	cout << "Dexterity:	"		<< Hero::getDexterity()	<< endl	;
	cout << "Agility:	"		<< Hero::getAgility()	<< endl ;
	cout << "Money:		"		<< Hero::getMoney()		<< endl ;
	cout << "Experience:	"	<< Hero::getExperience()<< "/" << Hero::getRequiredExperience() << endl ;
	cout << "---------------------------------------------" << endl << endl ;

	cout << "---------------------------------------------" << endl << endl ;
	cout << endl << "Hero holds: " << endl;
	if(Hero::getFirstHand() == Hero::getSecondHand() && Hero::getFirstHand() != NULL){
		cout << "Two handed: " << Hero::getFirstHand()->getName() << endl;
	}
	else{
		if(Hero::getFirstHand() != NULL){
			cout << "First hand: " << Hero::getFirstHand()->getName() << endl;
		}

		if(Hero::getSecondHand() != NULL){
			cout << "Second hand: " << Hero::getSecondHand()->getName() << endl;
		}

		if(Hero::getFirstHand() == NULL && Hero::getSecondHand() == NULL){
			cout << "Hero doesn't hold any weapons." << endl;
		}
	}
	cout << "---------------------------------------------" << endl << endl ;

	cout << "Hero wears:" << endl;
	if(Hero::getHeadArmor() != NULL){
		cout << "Head Armor: " << Hero::getHeadArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any head armor" << endl;
	}
	
	if(Hero::getBodyArmor() != NULL){
		cout << "Body Armor: " << Hero::getBodyArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any body armor" << endl;
	}
	if(Hero::getHandsArmor() != NULL){
		cout << "Hand Armor: " << Hero::getHandsArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any hand armor" << endl;
	}	

	if(Hero::getLegsArmor() != NULL){
		cout << "Leg Armor: " << Hero::getLegsArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any leg armor" << endl;
	}

	cout << "---------------------------------------------" << endl << endl ;
}

void Sorcerer::levelUp(void)	//leveling up the sorcerer
{	
	int stren = Hero::getStrength();
	int agil  = Hero::getAgility();
	int dext  = Hero::getDexterity();

	unsigned int max_hp = Living::getMaxHealth();	//take the statistics
	unsigned int max_mp = Hero::getMaxMagic();

	int cur_hp = Living::getHealth();
	int cur_mp = Hero::getMagic();

	cur_hp = cur_hp + cur_hp * 0.15 ;
	cur_mp = cur_mp + cur_mp * 0.15 ;

	max_hp = max_hp + max_hp * 0.25 ;		//increase the statistics
	max_mp = max_mp + max_mp * 0.25 ;

	stren = stren + stren * 0.25 ;
	agil  = agil  + agil  * 0.5 ;
	dext  = dext  + dext  * 0.5 ; 

	Hero::setStrength(stren);
	Hero::setAgility(agil);
	Hero::setDexterity(dext);

	Hero::setCurrentMagic(cur_mp);
	Living::setCurrentHealth(cur_hp);	//replace the statistics

	Hero::setMaxMagic(max_mp);
	Living::setMaxHealth(max_hp);

	Living::setLevel();

}

Sorcerer::~Sorcerer(void)
{
	//cout << "A Sorcerer destroyed..." << endl ;
}

//paladin constructor
Paladin::Paladin(const string& nam,const int& hp,const unsigned int& lvl, const int& mp ,const int& st
,const int& dext,const int&	agil,const int& def,const unsigned int& mon,const unsigned int& xp,
const unsigned int& posX,const unsigned int& posY)
: Hero(nam,hp,lvl,mp,st,dext,agil,def,mon,xp,posX,posY)
{
	//cout << "A Paladin created..." << endl;
}


void Paladin::displayStats(void)	//showing info about the paladin
{
	cout << "---------------------------------------------" << endl ;
	cout << "Hero Statistics:"	<< endl ;
	cout << "Paladin Name:	"	<< Living::getName()	<< endl ;
	cout << "Level:		" 		<< Living::getLevel()	<< endl ;
	cout << "Health Power:	"	<< Living::getHealth()	<< "/" << Living::getMaxHealth() << endl ;
	cout << "Magic Power:	"	<< Hero::getMagic()		<< "/" << Hero::getMaxMagic() << endl	;
	cout << "Strength:	"		<< Hero::getStrength()	<< endl ;
	cout << "Defense Points: "  << Hero::getDefensePoints() << endl; 
	cout << "Dexterity:	"		<< Hero::getDexterity()	<< endl	;
	cout << "Agility:	"		<< Hero::getAgility()	<< endl ;
	cout << "Money:		"		<< Hero::getMoney()		<< endl ;
	cout << "Experience:	"	<< Hero::getExperience()<< "/" << Hero::getRequiredExperience() << endl ;
	cout << "---------------------------------------------" << endl << endl ;

	cout << "---------------------------------------------" << endl << endl ;
	cout << endl << "Hero holds: " << endl;//items of the hero
	if(Hero::getFirstHand() == Hero::getSecondHand() && Hero::getFirstHand() != NULL){
		cout << "Two handed: " << Hero::getFirstHand()->getName() << endl;
	}
	else{
		if(Hero::getFirstHand() != NULL){
			cout << "First hand: " << Hero::getFirstHand()->getName() << endl;
		}

		if(Hero::getSecondHand() != NULL){
			cout << "Second hand: " << Hero::getSecondHand()->getName() << endl;
		}

		if(Hero::getFirstHand() == NULL && Hero::getSecondHand() == NULL){
			cout << "Hero doesn't hold any weapons." << endl;
		}
	}
	cout << "---------------------------------------------" << endl << endl ;

	cout << "Hero wears:" << endl;
	if(Hero::getHeadArmor() != NULL){
		cout << "Head Armor: " << Hero::getHeadArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any head armor" << endl;
	}
	
	if(Hero::getBodyArmor() != NULL){
		cout << "Body Armor: " << Hero::getBodyArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any body armor" << endl;
	}
	if(Hero::getHandsArmor() != NULL){
		cout << "Hand Armor: " << Hero::getHandsArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any hand armor" << endl;
	}	

	if(Hero::getLegsArmor() != NULL){
		cout << "Leg Armor: " << Hero::getLegsArmor()->getName() << endl;
	}
	else{
		cout << "Doesn't wear any leg armor" << endl;
	}

	cout << "---------------------------------------------" << endl << endl ;
}

void Paladin::levelUp(void)	//leveling up the paladin
{	
	unsigned int stren = Hero::getStrength();
	unsigned int agil  = Hero::getAgility();
	unsigned int dext  = Hero::getDexterity();	//take the statistics

	unsigned int max_hp = Living::getMaxHealth();
	unsigned int max_mp = Hero::getMaxMagic();

	int cur_hp = Living::getHealth();
	int cur_mp = Hero::getMagic();

	cur_hp = cur_hp + cur_hp * 0.15 ;
	cur_mp = cur_mp + cur_mp * 0.15 ;

	max_hp = max_hp + max_hp * 0.25 ;	//increase the statistics
	max_mp = max_mp + max_mp * 0.25 ;

	stren = stren + stren * 0.5 ;
	agil  = agil  + agil  * 0.25 ;
	dext  = dext  + dext  * 0.5 ; 



	Hero::setStrength(stren);
	Hero::setAgility(agil);
	Hero::setDexterity(dext);

	Hero::setCurrentMagic(cur_mp);	//replace the statistics
	Living::setCurrentHealth(cur_hp);

	Hero::setMaxMagic(max_mp);
	Living::setMaxHealth(max_hp);

	Living::setLevel();

}

Paladin::~Paladin(void)
{
	//cout << "A Paladin destroyed..." << endl ;
}