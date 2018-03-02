#ifndef __LIVING__
#define __LIVING__

#include <iostream>
#include <string>
#include <list>
#include <cstdlib>

#include "../Item/Item.hpp"
#include "../Spell/Spells.hpp"

enum Direction{UP,DOWN,LEFT,RIGHT};
enum HeroClass{WARRIOR,PALADIN,SORCERER}; //Need this at the constructor of Grid

class Living
{

private:
	const std::string name;
	unsigned int maxHealthPower;
	int currHealthPower;
	unsigned int level;
	bool fainted;

public:
	Living(const std::string&,const unsigned int&,const unsigned int&);

	const std::string& getName() const{ return name; }
	const unsigned int& getLevel() const{ return level; }
	const int& getHealth() const{ return currHealthPower; }
	const unsigned int& getMaxHealth() const { return maxHealthPower ;}	
	const bool& isFainted() const{ return fainted; }

	void setLevel() { level++; }
	void setMaxHealth(const unsigned int& maxHP)	{ maxHealthPower = maxHP ; }
	void setCurrentHealth(const int& curHP) 		{ currHealthPower = curHP ;}	
	virtual void  displayStats() = 0 ;
	
	void reduceHealth(const int&);
	void increaseHealth(const int&); 
	void setHalfHealth() { currHealthPower = maxHealthPower/2 ;}
	

	virtual ~Living();
};

class Monster ;	//forward decleration

class Hero : public Living {

private:
	unsigned int maxMagicPower ;
	int currMagicPower ;
	unsigned int strength ;
	unsigned int dexterity ;
	unsigned int agility ;
	unsigned int defensePoints;

	unsigned int money ;

	unsigned int RequiredExperience;
	unsigned int experience ;

	unsigned int positionX, positionY;

	Weapon* first_hand;
	Weapon* second_hand;

	Armor* head;
	Armor* body;
	Armor* hands;
	Armor* legs;


	std::list <Spell*> SpellList ; 	//the spells of the hero
	std::list <Item*> ItemList ;	//the items of the hero

	static const unsigned int InitialRequiredExperience;      //It's the Required Experience to proceed from level 1 to level 2 

public:
	Hero(const std::string&,const unsigned int&,const unsigned int&,const  unsigned int&,
	const unsigned int&,const unsigned int&,const unsigned int&,const unsigned int&,
	const unsigned int&,const unsigned int&,const unsigned int&,const unsigned int&);

	const unsigned int& getPositionX() const{ return positionX; }
	const unsigned int& getPositionY() const{ return positionY; }
	const int& getMagic() const 	{ return currMagicPower;}
	const unsigned int& getStrength() const 	{ return strength ;	}
	const unsigned int& getDexterity() const { return dexterity; }
	const unsigned int& getAgility() const 	{ return agility ; 	}
	const unsigned int& getDefensePoints() const{ return defensePoints; }
	const unsigned int& getMaxMagic() const { return maxMagicPower ;}	

	const unsigned int& getMoney() const 		{ return money ; 	}

	const unsigned int& getRequiredExperience() const { return RequiredExperience; }
	const unsigned int& getExperience() const 	{ return experience ;}

	const std::list<Item*>& getItems() const { return ItemList; }
	const std::list<Spell*>& getSpells() const { return SpellList; }

	const Weapon* getFirstHand() const{ return first_hand; }
	const Weapon* getSecondHand() const{ return second_hand; }

	const Armor* getHeadArmor() const{ return head; }
	const Armor* getBodyArmor() const{ return body; }
	const Armor* getHandsArmor() const{ return hands; }
	const Armor* getLegsArmor() const{ return legs; }

	void setMaxMagic(const unsigned int& maxMP ) { maxMagicPower = maxMP ;}
	void setCurrentMagic(const int& curMP) 		{ currMagicPower = curMP ;}
	void setDefensePoints(const unsigned int& d) { defensePoints = d; }
	void setStrength(const unsigned int& s)	{ strength = s ;}
	void setDexterity(const unsigned int& d)	{ dexterity = d;}
	void setAgility(const unsigned int& a)	{ agility = a ;	}

	void setPositionX(const unsigned int& x){ positionX = x; }
	void setPositionY(const unsigned int& y){ positionY = y; } 

	void setMoney(const int&);
	void loseMoney() { money = money/2 ;}	
	void increaseMoney(const unsigned int& k) { money = money + k; }		
	void setExperience(const unsigned int& );
	void reduceMagic(const int&);
	void increaseMagic(const int& )	;	

	void Move(const Direction&); 
	void CheckInventory(); 
	void Equip(std::list<Item*>::iterator&); 
	void UsePotion(std::list<Item*>::iterator&);
	void Drop(std::list<Item*>::iterator&);     
	void Drop(std::list<Spell*>::iterator&);    
	void Buy(std::list<Item*>::iterator&);      
	void Buy(std::list<Spell*>::iterator&);     
	void Sell(std::list<Item*>::iterator&);      
	void Sell(std::list<Spell*>::iterator&);      


	void Attack(Monster&);
	int castSpell(Monster&);
	std::list<Spell*>::iterator chooseSpell();
	std::list<Item*>::iterator choosePotion();

	int pickAttack();
	int pickMonster(const Monster**&,const unsigned int&);

	int changeWeapon();
	int changeArmor();
	virtual void levelUp(void) = 0 ;

	~Hero();
};


class Warrior : public Hero {
public:
	Warrior(const std::string&,const int&,const unsigned int&,const int&,
	const int&,const int&,const int&,const int& ,const unsigned int&,
	const unsigned int&,const unsigned int&,const unsigned int&);

	void levelUp();
	void displayStats();

	~Warrior();
};

class Sorcerer : public Hero {
public:
	Sorcerer(const std::string&,const int&,const unsigned int&,const int&,const int&
	,const int&,const int&,const int& ,const unsigned int&,const unsigned int&,
	const unsigned int&,const unsigned int&);

	void levelUp();
	void displayStats();

	~Sorcerer();
};


class Paladin : public Hero {
public:
	Paladin(const std::string&,const int&,const unsigned int&,const int&,const int&,
	const int&,const int&,const int& ,const unsigned int&,const unsigned int&,
	const unsigned int&,const unsigned int&);

	void levelUp();
	void displayStats();

	~Paladin();

};


class Monster: public Living
{

private:
	int min_damage;
	int max_damage;
	int armor;
	double dodge_possibility;

	std::list<Spell*> FaintedSpellList ; //the fainted spells that has the monster from previous rounds

public:
	Monster(const std::string&,const int&,const unsigned int&,const int&,const int&,const int&,const double&);

	const int& getMinDamage() const{ return min_damage; }
	const int& getMaxDamage() const{ return max_damage; }
	const int& getArmor() const{ return armor; }
	const double& getDodgePossibility() const{ return dodge_possibility; }

	void setDodgePossibility(double d) { dodge_possibility = d ;}
	void setArmor(int a) { armor = a ;}
	void setMinDamage(int d) { min_damage = d ; } 
	void setMaxDamage(int d) { max_damage = d ; }	

	void increaseMinDamage(const int& damage){ min_damage += damage; }
	void increaseMaxDamage(const int& damage){ max_damage += damage; }
	void increaseArmor(const int& armor_){ armor += armor_; }
	void increaseDodgePossibility(const double& possibility);//{ dodge_possibility += possibility; }

	void addSpell(Spell*);
	
	void checkFaintedSpells();
	void  Attack(Hero&) ;

	~Monster();
};

class Dragon: public Monster
{

public:
	Dragon(const std::string&,const int&,const unsigned int&,const int&,const int&,const int&,const double&);

	void displayStats();

	~Dragon();
};

class Exoskeleton: public Monster
{

public:
	Exoskeleton(const std::string&,const int&,const unsigned int&,const int&,const int&,const int&,const double&);

	void displayStats();

	~Exoskeleton();
};

class Spirit: public Monster
{

public:
	Spirit(const std::string&,const int&,const unsigned int&,const int&,const int&,const int&,const double&);

	void displayStats();

	~Spirit();
};

#endif