#ifndef __ITEM__
#define __ITEM__

#include <iostream>
#include <string>

enum body_part{HEAD,BODY,HANDS,LEGS};
enum stat{HEALTH,MAGIC,STRENGTH,DEXTERITY,AGILITY}; 
enum ItemType{WEAPON,ARMOR,POTION};


class Item
{

private:

	const std::string name;
	const unsigned int value;
	const unsigned int min_level;
	const ItemType Type;

public:

	Item(const std::string&,const unsigned int&,const unsigned int&,const ItemType&);

	Item(const Item&);

	virtual void print() const = 0;

	const std::string& getName() const{ return name; }
	const unsigned int& getValue() const{ return value; }
	const unsigned int& getMinLevel() const{ return min_level; }
	const ItemType& getType() const{ return Type; }

	virtual ~Item();
};

class Weapon: public Item
{

private:
	const unsigned int damage;
	const bool one_handed;     //0 for two handed, 1 for one handed

public:

	Weapon(const std::string&,const unsigned int&,const unsigned int&,const unsigned int&,const bool&);

	Weapon(const Weapon&);

	void print() const;

	const unsigned int& getDamage() const{ return damage; }
	const bool& isOneHanded() const{ return one_handed; }

	~Weapon();	

};

class Armor: public Item
{

private:
	const unsigned int defense_points;
	const body_part part;

public:	
	Armor(const std::string&,const unsigned int&,const unsigned int&,const unsigned int&,const body_part&);

	Armor(const Armor&);

	void print() const;

	const body_part& getAppliedPart() const{ return part; }
	const unsigned int& getDefensePoints() const{ return defense_points; }

	~Armor();
};

class Potion: public Item
{

private:
	const stat statistic; 				//It's the statistic that will be increased
	const unsigned int increase_value;

public: 
	Potion(const std::string&,const unsigned int&,const unsigned int&,const stat&,const unsigned int&);

	Potion(const Potion&);
	
	void print() const;
	
	const stat& getIncreasedStatistic() const{return statistic; }
	const unsigned int& getIncreasedValue() const{return increase_value; }

	~Potion();
};

#endif