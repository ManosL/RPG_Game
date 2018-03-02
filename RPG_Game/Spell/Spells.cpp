#include <iostream>

#include "Spells.hpp"
#include "../Living/Living.hpp"

using namespace std ;

LightingSpell::LightingSpell(const string& nam ,const unsigned int& pr ,const unsigned int& minL ,const int& mindmg ,const int& maxdmg
,const int& magpow, const unsigned int& roundD ,const double& rate_do)
:  Spell(nam,pr,minL,mindmg,maxdmg,magpow,roundD,LIGHTING) , rate_Dodge(rate_do)
{
	//cout << "A Lighting Spell is created..." << endl ;
}

LightingSpell::LightingSpell(const LightingSpell& other):Spell(other), reduce_Dodge(other.reduce_Dodge)
{
	//LightingSpell copied
}

//function to use the lighting spell
void LightingSpell::useSpell(Monster& mon,int dex)
{
	mon.addSpell(this);  //add the spell in the fainted-spell-list of the monster

	double rate = this->getRateDodge();	//get rate-dodge

	double MonsterDodge = mon.getDodgePossibility();//get monster's dodge

	double reduce = (MonsterDodge * rate ) ;//the number of reduce 
	
	MonsterDodge = MonsterDodge - reduce ; //formula 

	if (MonsterDodge > 0.0)	//set the new dodge
		mon.setDodgePossibility(MonsterDodge) ;
	else
		mon.setDodgePossibility(0.01);

	this->setReduceDodge(reduce);	
	//set the number of reduced-dodge to have it when the effect of the spell will end

	//damage of the spell
	int damage = rand()%(Spell::getMaxDamage() - Spell::getMinDamage() ) + Spell::getMinDamage() ;
 	
	int dmg =  (damage * damage)/(damage + mon.getArmor() );//attack formula

 	mon.reduceHealth(dmg);

}

//lighting statistics
void LightingSpell::print() const 
{
	cout << "Ice Spell Details:" << endl ;
	cout << "Name:		" << getName() << endl ;
	cout << "Price:		" << getPrice() << endl ;
	cout << "Minimum Level:	" << getMinLevel() << endl ;
	cout << "Damage:		" << "[" << getMinDamage() << "," << getMaxDamage() << "]" << endl ;
	cout << "Magic Power:	" << getMagic() << endl;
	cout << "Round Duration:	" << getRoundDuration() << endl ;
	cout << "Reduced Dodge:	" << reduce_Dodge << endl;

	cout << endl << endl;
}

LightingSpell::~LightingSpell()
{
	//cout << "A Lighting Spell is destroyed..." << endl ;
}

FireSpell::FireSpell(const string& nam ,const unsigned int& pr ,const unsigned int& minL ,const int& mindmg ,const int& maxdmg
,const int& magpow, const unsigned int& roundD ,const double& rate_Arm)
: Spell(nam,pr,minL,mindmg,maxdmg,magpow,roundD,FIRE) , rate_Armor(rate_Arm)
{
	//cout << "A Fire Spell is created..." << endl ;
}

FireSpell::FireSpell(const FireSpell& other): Spell(other), reduce_Armor(other.reduce_Armor)
{
	//FireSpell copied
}

//firespell use
void FireSpell::useSpell(Monster& mon,int dex)
{
	mon.addSpell(this); //add the spell in the fainted-spell-list of the monster

	double rate = this->getRateArmor();

	int  MonsterArmor = mon.getArmor();

	int reduce = (MonsterArmor * rate) + dex/10 ; //the reduced number
	
	MonsterArmor = MonsterArmor - reduce   ; //formula

	if (MonsterArmor > 0)	//set the new armor of the monster
		mon.setArmor(MonsterArmor) ;
	else
		mon.setArmor(5);
	
	this->setReduceArmor(reduce); //save the reduced number

	//damage of the spell
	int damage = rand()%(Spell::getMaxDamage() - Spell::getMinDamage() ) + Spell::getMinDamage() ;
 	
	int dmg =  (damage * damage)/(damage + mon.getArmor() );//attack formula

 	mon.reduceHealth(dmg);

}
//firespell statistics
void FireSpell::print() const 
{
	cout << "Fire Spell Details:" << endl ;
	cout << "Name:		" << getName() << endl ;
	cout << "Price:		" << getPrice() << endl ;
	cout << "Minimum Level:	" << getMinLevel() << endl ;
	cout << "Damage:		" << "[" << getMinDamage() << "," << getMaxDamage() << "]" << endl ;
	cout << "Magic Power:	" << getMagic() << endl;
	cout << "Round Duration:	" << getRoundDuration() << endl ;
	cout << "Reduced Armor:	" << reduce_Armor << endl;

	cout << endl << endl;
}

FireSpell::~FireSpell()
{
	//cout << "A Fire Spell is destroyed..." << endl ;
}


IceSpell::IceSpell(const string& nam ,const unsigned int& pr ,const unsigned int& minL ,const int& mindmg ,const int& maxdmg
,const int& magpow, const unsigned int& roundD ,const double& rate_Dmg)
: Spell(nam,pr,minL,mindmg,maxdmg,magpow,roundD,ICE) , rate_Damage(rate_Dmg)
{
	//cout << "An Ice Spell is created..." << endl;
}

IceSpell::IceSpell(const IceSpell& other): Spell(other), reduce_Damage(other.reduce_Damage)
{
	//IceSpell Copied
}

//icespell use
void IceSpell::useSpell(Monster& mon,int dex)
{
	mon.addSpell(this);	//add the spell in the fainted-spell-list of the monster

	double rate = this->getRateDamage();

	int  MonsterMinDamage = mon.getMinDamage();
	int  MonsterMaxDamage = mon.getMaxDamage();

	int reduce = (MonsterMaxDamage * rate) + dex/10; //the reduced number 
	
	MonsterMinDamage = MonsterMinDamage - reduce ;	//formula
	MonsterMaxDamage = MonsterMaxDamage - reduce ;

	if (MonsterMinDamage > 0)//set the new damage-range
		mon.setMinDamage(MonsterMinDamage) ;	
	else
		mon.setMinDamage(0);

	if (MonsterMaxDamage > 0)
		mon.setMaxDamage(MonsterMaxDamage) ;
	else
		mon.setMaxDamage(10);
	
	this->setReduceDamage(reduce);//save the reduced number

	//damage of the spell
	int damage = rand()%(Spell::getMaxDamage() - Spell::getMinDamage() ) + Spell::getMinDamage() ;
 	
	int dmg =  (damage * damage)/(damage + mon.getArmor() );//attack formula

 	mon.reduceHealth(dmg);

}

//icespell statistics
void IceSpell::print() const 
{
	cout << "Ice Spell Details:" << endl ;
	cout << "Name:		" << getName() << endl ;
	cout << "Price:		" << getPrice() << endl ;
	cout << "Minimum Level:	" << getMinLevel() << endl ;
	cout << "Damage:		" << "[" << getMinDamage() << "," << getMaxDamage() << "]" << endl ;
	cout << "Magic Power:	" << getMagic() << endl;
	cout << "Round Duration:	" << getRoundDuration() << endl ;
	cout << "Reduced Damage:	" << reduce_Damage << endl;

	cout << endl << endl;
}

IceSpell::~IceSpell()
{
	//cout << "An Ice Spell is destroyed..." << endl ;
}


Spell::Spell(const string& nam ,const unsigned int& pr ,const unsigned int& minL ,
const int& mindmg ,const int& maxdmg,const int& magpow, const unsigned int& roundD, const SpellType& Type_)
: name(nam) , price(pr) , min_Level(minL) , minDamage(mindmg) , maxDamage(maxdmg) , magicPower(magpow)
 , roundDuration(roundD), Type(Type_)
{
	//cout << "A spell created..." << endl ;
}

Spell::Spell(const Spell& other): name(other.name), price(other.price), min_Level(other.min_Level),
minDamage(other.minDamage), maxDamage(other.maxDamage), magicPower(other.magicPower), roundDuration(other.roundDuration),
Type(other.Type)
{
	//Spell copied
}

Spell::~Spell(void)
{
	//cout << "A spell destroyed..." << endl ;
}