#include "BattleArena.hpp"

using namespace std;

BattleArena::BattleArena(Hero** ptrHeroes_, const unsigned int& numHeroes_,
Monster** ptrMonsters_,const unsigned int& numMonsters_):
ptrHeroes(ptrHeroes_),numHeroes(numHeroes_),ptrMonsters(ptrMonsters_),
numMonsters(numMonsters_)
{
    //Battle Arena constructed, I only want to change pointers not to have another copy
}

int BattleArena::battle()
{
        unsigned int round = 1 ;

        bool hero_flag    = false ;
        int ch ;
        string temp;

        for (unsigned int i = 0 ; i < numHeroes ; i++)
        {
                if (ptrHeroes[i]->getHealth() > 0)//if at least one hero is alive hero-flag is true
                        hero_flag = true ;
        }

        bool monster_flag = false ;

        for (unsigned int i = 0 ; i < numMonsters ; i++)
        {
                if (ptrMonsters[i]->getHealth() > 0)//if at least one monster is alive monster-flag is true
                        monster_flag = true ;
        }

        int target;
        int flag; 

        //the battle ends when hero-flag or monster-flag is false
        while( (hero_flag == true ) && (monster_flag == true) )
        {        
                cout << "\033[2J\033[1;1H";
       			cout << "Hero Turn: " << endl << endl ;
                //heroes turn
                for (unsigned int i = 0 ; i < numHeroes ; i++)
                {        
                        if ( ptrHeroes[i]->getHealth() > 0)//if hero is alive
                        {       
                                flag = 0 ;
                                cout << "\033[2J\033[1;1H";

                                int attack = ptrHeroes[i]->pickAttack();//pick the move of attack you want
                                int target ;


                                if (attack == 1) //normal attack
                                {        //pick which monster to attack
                                        target = ptrHeroes[i]->pickMonster((const Monster**&) ptrMonsters , numMonsters);
                                        ptrHeroes[i]->Attack( *ptrMonsters[target] ); //attack the picked monster
                                        flag = 1;

                                }
                                else if (attack == 2) //spell attack
                                {        //pick which monster to cast-spell
                                        target = ptrHeroes[i]->pickMonster((const Monster**&) ptrMonsters , numMonsters);
                                        flag = ptrHeroes[i]->castSpell( *ptrMonsters[target]);//execute the spell to the picked monster
										
										if(flag == -1){//when cast spell returns -1 means the hero has not enough magic power

											flag = 0;

											cout << "\033[2J\033[1;1H";

                                			cout << "The hero has not enough magic power to execute the Spell." << endl;

											cout << "Press c to continue the battle" << endl;
											while((ch = getchar_silent()) != 'c'){
												//DO NOTHING
											}                                 			
										}
										else if(flag == 0){
                                            //when castspell returns 0 means the hero has no spells
											cout << "\033[2J\033[1;1H";

											cout << "You don't have any spells to cast" << endl;

											cout << "Press c to continue the battle" << endl;
											while((ch = getchar_silent()) != 'c'){
												//DO NOTHING
											} 
										}
                                }
                                else if (attack == 3){  //use potion
                                        list<Item*>::iterator potion = ptrHeroes[i]->choosePotion();//choose the potion you want
                                        
                                        if((potion != ptrHeroes[i]->getItems().end()) && ((*potion)->getType() == POTION ))        
                                        {       ptrHeroes[i]->UsePotion(potion);//use the potion
                                                flag = 1;
                                        }
                                        else{
                                            flag = 0 ;//the hero has no potions
											
											cout << "\033[2J\033[1;1H";

											cout << "You don't have any potions" << endl;

											cout << "Press c to continue the battle" << endl;
											while((ch = getchar_silent()) != 'c'){
												//DO NOTHING
											}
										}                                                
                                }
                                else if (attack == 4){  //change weapon
                                        flag = ptrHeroes[i]->changeWeapon();//change the weapon of the hero

										if(flag == 0){
											cout << "\033[2J\033[1;1H";  //the hero has no weapons

											cout << "You don't have any Weapons to equip" << endl;
											
											cout << "Press c to continue the battle" << endl;
											while((ch = getchar_silent()) != 'c'){
												//DO NOTHING
											}										
                                		}
								}			
                                else if (attack == 5){  //change armor
                                        flag = ptrHeroes[i]->changeArmor(); //change the armor of the hero

										if(flag == 0){
											cout << "\033[2J\033[1;1H";  //the hero has no armors

											cout << "You don't have any armor to equip" << endl;
											
											cout << "Press c to continue the battle" << endl;
											while((ch = getchar_silent()) != 'c'){
												//DO NOTHING
											}
										}

                                }
                                else if (attack == 6){  //see statistics
                                        cout << "\033[2J\033[1;1H";

                                        ptrHeroes[i]->displayStats();

                                        cout << "Press c to continue the battle" << endl;
                                        while((ch = getchar_silent()) != 'c'){
                                                //DO NOTHING
                                        }

                                        flag = 0;
                                }
 								   //when flag=0 means that the hero couldnt execute the order you gave 
   									 //the menu-attack of this hero is again available so pick another option 
                                if (flag == 0) 
                                        i-- ;//to not go to the next hero
                        }

						monster_flag = false;

		        		for (unsigned int i = 0 ; i < numMonsters ; i++)		//Checking if there is any alive monster to continue the battle
                		{
                		    if (ptrMonsters[i]->getHealth() > 0)//if there is at least one alive monster
                		    {
                		            monster_flag = true ;   //make the monster-flag true
                		    }
                		}

						if(monster_flag == false) break; //If the hero doesn't have any monster to attack				
                }

                //monsters turn

				if(monster_flag)   //This message will be printed only if at least one monster is able to attack
                cout << endl << "Monsters Turn: " << endl << endl ;

                for (unsigned int i=0 ; i < numMonsters ; i++)
                {
                        do{     //pick an alive hero to attack
                                target = rand() % numHeroes;
                        }while( ptrHeroes[target]->getHealth() < 0 );

                        if (ptrHeroes[target]->getHealth() > 0 && ptrMonsters[i]->getHealth() > 0)   //attack this hero if he is alive and check if the monster can attack
                                ptrMonsters[i]->Attack( *ptrHeroes[target] );
                }

                
                cout << endl << endl << "To see the statistics press y else press n" << endl ;

                ch = getchar_silent();

                cout << "\033[2J\033[1;1H";
                
                if (ch == 'y')
                {       //show the heroes statistics
                        for (unsigned int i = 0 ; i < numHeroes ; i++)
                                if (ptrHeroes[i]->getHealth() > 0){
                                        ptrHeroes[i]->displayStats();
                                }        
                        //show the monsters statistics
                        for (unsigned int i = 0 ; i < numMonsters ; i++)
                                if (ptrMonsters[i]->getHealth() > 0){
                                        ptrMonsters[i]->displayStats();
                                }

                        cout << endl << endl << "Press c to continue" << endl;        
                        while((ch = getchar_silent()) != 'c'){}        
                }

                round++;  //count the rounds

                hero_flag    = false ;//to check if there is at least one alive hero

                for (unsigned int i = 0 ; i < numHeroes ; i++)
                {
                        if (ptrHeroes[i]->getHealth() > 0)//if there is at least one alive hero
                        {        hero_flag = true ; //make the hero-flag true
                                ptrHeroes[i]->increaseMagic( ptrHeroes[i]->getMagic() * 0.2); //increase magic and health
                                ptrHeroes[i]->increaseHealth( ptrHeroes[i]->getHealth() * 0.2);  //get increased by 20%
                        }
                }

                monster_flag = false ;//to check if there is at least one alive monster

                for (unsigned int i = 0 ; i < numMonsters ; i++)
                {
                        if (ptrMonsters[i]->getHealth() > 0)//if there is at least one alive monster
                        {
                                monster_flag = true ;   //make the monster-flag true
                                ptrMonsters[i]->increaseHealth  ( ptrMonsters[i]->getHealth() * 0.2); //get increased by 20%
                                //check the fainted spell-list of the monster
                                ptrMonsters[i]->checkFaintedSpells();
                        }
                }
                 
        }

        if (hero_flag == true)//the heroes have won
        {
                cout << "\033[2J\033[1;1H";
                cout << "Heroes won " << endl;
                for (unsigned int i = 0 ; i < numHeroes ; i++)
                {       //make the dead heroes helath to the half
                        if (ptrHeroes[i]->getHealth() <= 0)
                                ptrHeroes[i]->setHalfHealth();
                            //give money and experience to the heroes
                        ptrHeroes[i]->increaseMoney( ptrHeroes[i]->getLevel() * numMonsters * 100);
                        ptrHeroes[i]->setExperience( ptrHeroes[i]->getLevel() * numMonsters * 10);
                }

                cout << "Press c to continue" << endl;
                while((ch = getchar_silent()) != 'c'){
                        //DO NOTHING
                }

                return 0;                
        }
        else
        {       //the monsters have won
				cout << "\033[2J\033[1;1H";
                cout << "Monsters Won" << endl;
                for (unsigned int i = 0 ; i < numHeroes ; i++)
                {
                        ptrHeroes[i]->loseMoney();//take the half money of the heroes
                        ptrHeroes[i]->setHalfHealth();  //set the helath of the heroes to the half
                }

                cout << "Press c to continue" << endl;
                while((ch = getchar_silent()) != 'c'){
                        //DO NOTHING
                }

                return 1;                
        }

}    


//destructor of battlearena
BattleArena::~BattleArena(){

    for(unsigned int i = 0;i < numMonsters;i++){
        delete ptrMonsters[i];
    }

    delete[] ptrMonsters;
}