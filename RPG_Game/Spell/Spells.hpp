#ifndef _SPELLS_
#define _SPELLS_

enum SpellType{ICE,FIRE,LIGHTING};

class Monster;

class Spell {
private:
	const std::string name ;
	unsigned int  price ;
	const unsigned int min_Level ;
	int minDamage ;
	int maxDamage ;
	int magicPower ;

	unsigned int roundDuration ;	//the rounds-effect of the spell

	const SpellType Type;

public:
	Spell(const std::string& ,const unsigned int& ,const unsigned int&,
	const int&,const int& ,const int& ,const unsigned int&,const SpellType&);

	Spell(const Spell&);

	const std::string& getName() const{ return name; }
	const unsigned int& getPrice() const {return price; }
	const unsigned int& getMinLevel() const{ return min_Level; }
	const int& getMinDamage() const { return minDamage; }
	const int& getMaxDamage() const {return maxDamage; }
	const int& getMagic() const { return magicPower; }
	const SpellType& getSpellType() const { return Type; }

	const unsigned int& getRoundDuration() const { return roundDuration ;}
	void reduceRoundDuration() { roundDuration-- ;}

	virtual void print() const = 0 ;

	virtual void useSpell(Monster&,int) = 0 ;

	virtual ~Spell();
};


class IceSpell : public Spell {
private:
	double rate_Damage ;	//the reduced-rate damage 
	int reduce_Damage ;		//the number of reduced damage
public:
	IceSpell(const std::string& ,const unsigned int& ,const unsigned int&,
	const int& ,const int& ,const int& ,const unsigned int&,const double&);

	IceSpell(const IceSpell&);

	const double& getRateDamage() const { return rate_Damage ; }
	void setReduceDamage(int r ) { reduce_Damage = r ; }
	const int& getReduce() const { return reduce_Damage ;}

	void print(void) const ;
	void useSpell(Monster&,int );
	~IceSpell(void);
};

class FireSpell : public Spell {
private:
	double rate_Armor ;		//the reduced-rate armor
	int reduce_Armor ;		//the number of reduced armor
public:
	FireSpell(const std::string& ,const unsigned int& ,const unsigned int&,
	const int& ,const int& ,const int&,const unsigned int& ,const double&);

	FireSpell(const FireSpell&);

	const double& getRateArmor() const { return rate_Armor ; }
	void setReduceArmor(int r) { reduce_Armor = r ;}
	const int& getReduce() const { return reduce_Armor; }

	void print() const ;
	void useSpell(Monster&, int );

	~FireSpell();
};


class LightingSpell : public Spell {
private:
	double rate_Dodge ;		//the reduced-rate dodge
	double reduce_Dodge ;	//the number of reduced-dodge
public:
	LightingSpell(const std::string& ,const unsigned int& ,const unsigned int&,
	const int& ,const int& ,const int&,const unsigned int& ,const double&);

	LightingSpell(const LightingSpell&);
	
	const double& getRateDodge() const { return rate_Dodge; }
	void setReduceDodge(double r) { reduce_Dodge = r ;}
	const double& getReduce() const {return reduce_Dodge ;} 
	
	void print() const ;
	void useSpell(Monster&, int );
	
	~LightingSpell();
};

#endif