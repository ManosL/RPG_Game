#include "Item.hpp"

using namespace std;

Item::Item(const std::string& name_,const unsigned int& value_,const unsigned int& min_level_,const ItemType& Type_): 
name(name_),value(value_),min_level(min_level_),Type(Type_)
{
	//Item constructed	
}

Item::Item(const Item& other): name(other.name), value(other.value), min_level(other.min_level),Type(other.Type)
{
	//Item copied
}

Item::~Item()
{
	//Blank body, I don't have to do something
}

Weapon::Weapon(const std::string& name_,const unsigned int& value_,const unsigned int& min_level_,const unsigned int& damage_,const bool& one_haned_):
Item(name_,value_,min_level_,WEAPON), damage(damage_), one_handed(one_haned_)
{
	//Weapon constructed
}

Weapon::Weapon(const Weapon& other): Item(other), damage(other.damage), one_handed(other.one_handed)
{
	//Weapon copied
}

//print waepon statistics
void Weapon::print() const
{
	cout << "Weapon Details:" << endl ;
	cout << "Name:		" << getName() << endl ;
	cout << "Price:		" << getValue() << endl ;
	cout << "Minimum Level:	" << getMinLevel() << endl ;
	cout << "Damage:		" << getDamage() << endl ;
	cout << "One handed:	" << isOneHanded() << endl;

	cout << endl << endl;	
}

Weapon::~Weapon()
{
	//Blank body,I don't have to do something
}

Armor::Armor(const std::string& name_,const unsigned int& value_,const unsigned int& min_level_,const unsigned int& defense_points_,const body_part& part_):
Item(name_,value_,min_level_,ARMOR), defense_points(defense_points_),part(part_)
{
	//Armor constructed
}

Armor::Armor(const Armor& other): Item(other), defense_points(other.defense_points), part(other.part)
{
	//Armor copied
}

//print armor statistics
void Armor::print() const
{
	cout << "Armor Details:" << endl ;
	cout << "Name:		" << getName() << endl ;
	cout << "Price:		" << getValue() << endl ;
	cout << "Minimum Level:	" << getMinLevel() << endl ;
	cout << "Defense Points:		"  << getDefensePoints() << endl ;

	cout<< "Body Part:	";
	switch(getAppliedPart()){
		case HEAD:
			cout << "Head" << endl;
			break;
		case BODY:
			cout << "Body" << endl;
			break;
		case HANDS:
			cout << "Hands" << endl;
			break;
		case LEGS:
			cout << "Legs" << endl;
			break;
	}

	cout << endl << endl;
}


Armor::~Armor()
{
	//Blank body,I don't have to do something
}

Potion::Potion(const std::string& name_,const unsigned int& value_,const unsigned int& min_level_,const stat& statistic_,const unsigned int& increase_value_):
Item(name_,value_,min_level_,POTION),statistic(statistic_),increase_value(increase_value_)
{
	//Potion constructed
}

Potion::Potion(const Potion& other): Item(other), statistic(other.statistic),increase_value(other.increase_value)
{
	//Potion copied
}

//print potion statistics
void Potion::print() const
{
	cout << "Potion Details:" << endl ;
	cout << "Name:		" << getName() << endl ;
	cout << "Price:		" << getValue() << endl ;
	cout << "Minimum Level:	" << getMinLevel() << endl ;
	cout << "Increases ";

	switch(getIncreasedStatistic()){
		case HEALTH:
			cout << "Health ";
			break;
		case MAGIC:
			cout << "Magic ";
			break;
		case STRENGTH:
			cout << "Strength ";
			break;
		case DEXTERITY:
			cout << "Dexterity ";
			break;
		case AGILITY:
			cout << "Agility ";
			break;
	}

	cout << "by " << getIncreasedValue() << " points" << endl;

	cout << endl << endl;

	return;	
}

Potion::~Potion()
{
	//Blank body,I don't have to do something
}