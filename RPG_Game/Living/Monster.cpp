#include "../Living/Living.hpp"

using namespace std;

//monster constructor
Monster::Monster(const std::string& name_,const int& healthPower_,const unsigned int& level_,
	const int& min_damage_,const int& max_damage_,const int& armor_,const double& dodge_possibility_):
	Living(name_,healthPower_,level_),min_damage(min_damage_),max_damage(max_damage_),armor(armor_),
	dodge_possibility(dodge_possibility_)
{
	//Monster, constructed
}

void Monster::addSpell(Spell* s)//add the spell in the fainted list of the monster
{
	FaintedSpellList.push_front(s);
}

void Monster::increaseDodgePossibility(const double& possibility)//increase the dodge
{
	dodge_possibility = possibility * dodge_possibility ;

}

//function of monster's attack
void Monster::Attack(Hero& Target){
	
	double accurate = Target.getAgility() * 0.1 ;

	double evasion = (this->getMaxDamage() - this->getMinDamage() ) * 0.05 ;

	double chance = ((accurate - evasion)/accurate);
	
	double posDodge = (double) rand() / (double)RAND_MAX;

	//check if the hero avoid the attack
	if ((chance < 0) || (posDodge > chance))
	{
		cout << "The hero avoided the attack..." << endl ;
		return ;
	}
	else	//take the specific damage from the damage range
	{	int damage = rand()%(this->getMaxDamage() - this->getMinDamage() ) + this->getMinDamage() ;
 	
		int dmg =  (damage * damage)/(damage + Target.getDefensePoints() );//attack formula

 		Target.reduceHealth(dmg);	//reduce the hero's health

	}
}	


//check the monster's fainted spell in every round
void Monster::checkFaintedSpells()
{
	for (list<Spell*>::iterator it = FaintedSpellList.begin() ; it != FaintedSpellList.end() ; it++)
	{
		int RoundDura = (*it)->getRoundDuration();

		if (RoundDura > 0)
		{	
			(*it)->reduceRoundDuration();//reduce the fainted round by one
		}
		else if (RoundDura == 0)//the spell's reaction is over
		{
			SpellType spell_type = (*it)->getSpellType();//get the type of the spell

			if (spell_type == ICE)//ice spell effects the damage
			{	//get the number of the reduced-statistic when the spell executed 

				int increase = ((IceSpell*) *it)->getReduce();	//to increase the statistic and recover from the spell

				int minDamage = this->getMinDamage();
				int maxDamage = this->getMaxDamage();

				minDamage = minDamage + increase ;//recover from the spell
				maxDamage = maxDamage + increase ;

				this->setMinDamage(minDamage);	//set the recovered values
				this->setMaxDamage(maxDamage);

			}
			else if (spell_type == FIRE)//fire spell effects the armor
			{	//same as before
				int increase = ((FireSpell*)*it)->getReduce();

				int armor = this->getArmor();

				armor = armor + increase ; 

				this->setArmor(armor) ;
			}
			else if (spell_type == LIGHTING)//lighting spell effects the dodge
			{	//same as before
				double increase = ((LightingSpell*)*it)->getReduce();

				double dodge = this->getDodgePossibility();

				dodge = dodge + increase ;

				this->setDodgePossibility(dodge);
			}

			delete *it ;		
			it = FaintedSpellList.erase(it);	//delete the spell from the fainted spell list
			it--;				
		}
	}
}

Monster::~Monster(){

	for(list<Spell*>::iterator it = FaintedSpellList.begin(); it != FaintedSpellList.end();){
		delete *it;
		it = FaintedSpellList.erase(it);
	}	
	
}

//dragon constructor
Dragon::Dragon(const std::string& name_,const int& healthPower_,const unsigned int& level_,
	const int& min_damage_,const int& max_damage_,const int& armor_,const double& dodge_possibility_):
	Monster(name_,healthPower_,level_,min_damage_,max_damage_,armor_,dodge_possibility_)
{
	for(unsigned int i = 2;i <= Living::getLevel();i++){				//Leveling up the monster
		Living::setMaxHealth(Living::getMaxHealth() + 0.2*Living::getMaxHealth());
		Living::setCurrentHealth(Living::getMaxHealth());
		
		Monster::increaseMinDamage(0.5*Monster::getMinDamage());
		Monster::increaseMaxDamage(0.5*Monster::getMaxDamage());
		Monster::increaseArmor(0.25*Monster::getArmor());
		Monster::increaseDodgePossibility(0.25*Monster::getDodgePossibility());
	}

}

//dragon statistics
void Dragon::displayStats(void)
{
	cout << "---------------------------------------------" << endl ;
	cout << "Dragon Statistics:	"	<< endl ;
	cout << "Dragon Name:		"	<< Living::getName()	<< endl ;
	cout << "Level:			" 		<< Living::getLevel()	<< endl ;
	cout << "Health Power:		"	<< Living::getHealth()	<< endl ;
	cout << "Damage Range:		"   << "[" << Monster::getMinDamage() << "," << Monster::getMaxDamage() << "]" << endl ;
	cout << "Armor:			"       << Monster::getArmor() << endl ;
	cout << "Dodge Possibility:	"<< Monster::getDodgePossibility() << endl ;
 	cout << "---------------------------------------------" << endl << endl ;

}

Dragon::~Dragon(){

	//Dragon,destroyed
}

//exoskeleton constructor
Exoskeleton::Exoskeleton(const std::string& name_,const int& healthPower_,const unsigned int& level_,
	const int& min_damage_,const int& max_damage_,const int& armor_,const double& dodge_possibility_):
	Monster(name_,healthPower_,level_,min_damage_,max_damage_,armor_,dodge_possibility_)
{
	for(unsigned int i = 2;i <= Living::getLevel();i++){			//Leveling up the monster
		Living::setMaxHealth(Living::getMaxHealth() + 0.2*Living::getMaxHealth());
		Living::setCurrentHealth(Living::getMaxHealth());

		Monster::increaseMinDamage(0.25*Monster::getMinDamage());
		Monster::increaseMaxDamage(0.25*Monster::getMaxDamage());
		Monster::increaseArmor(0.5*Monster::getArmor());
		Monster::increaseDodgePossibility(0.25*Monster::getDodgePossibility());
	}

}

//exoskeleton statistics
void Exoskeleton::displayStats(void)
{
	cout << "---------------------------------------------" << endl ;
	cout << "Exoskeleton Statistics:"	<< endl ;
	cout << "Exoskeleton Name:	"	<< Living::getName()	<< endl ;
	cout << "Level:			" 		<< Living::getLevel()	<< endl ;
	cout << "Health Power:		"	<< Living::getHealth()	<< endl ;
	cout << "Damage Range:		"   << "[" << Monster::getMinDamage() << "," << Monster::getMaxDamage() << "]" << endl ;
	cout << "Armor:			"       << Monster::getArmor() << endl ;
	cout << "Dodge Possibility:	"<< Monster::getDodgePossibility() << endl ;
 	cout << "---------------------------------------------" << endl << endl ;

}

Exoskeleton::~Exoskeleton(){

	//Exoskeleton,Destroyed
}

//spirit constructor
Spirit::Spirit(const std::string& name_,const int& healthPower_,const unsigned int& level_,
	const int& min_damage_,const int& max_damage_,const int& armor_,const double& dodge_possibility_):
	Monster(name_,healthPower_,level_,min_damage_,max_damage_,armor_,dodge_possibility_)
{
	for(unsigned int i = 2;i <= Living::getLevel();i++){					//Leveling up the monster
		Living::setMaxHealth(Living::getMaxHealth() + 0.2*Living::getMaxHealth());
		Living::setCurrentHealth(Living::getMaxHealth());	

		Monster::increaseMinDamage(0.25*Monster::getMinDamage());
		Monster::increaseMaxDamage(0.25*Monster::getMaxDamage());
		Monster::increaseArmor(0.25*Monster::getArmor());
		Monster::increaseDodgePossibility(0.5*Monster::getDodgePossibility());
	}

}

//spirit statistics
void Spirit::displayStats(void)
{
	cout << "---------------------------------------------" << endl ;
	cout << "Spirit Statistics:"	<< endl ;
	cout << "Spirit Name:		"	<< Living::getName()	<< endl ;
	cout << "Level:			" 		<< Living::getLevel()	<< endl ;
	cout << "Health Power:		"	<< Living::getHealth()	<< endl ;
	cout << "Damage Range:		"   << "[" << Monster::getMinDamage() << "," << Monster::getMaxDamage() << "]" << endl ;
	cout << "Armor:			"       << Monster::getArmor() << endl ;
	cout << "Dodge Possibility:	"<< Monster::getDodgePossibility() << endl ;
 	cout << "---------------------------------------------" << endl << endl ;

}


Spirit::~Spirit(){

	//Spirit Destroyed
}