#include "../Living/Living.hpp"

using namespace std;


Living::Living(const std::string& name_,const unsigned int& healthPower_,const unsigned int& level_ = 1):
				name(name_), maxHealthPower(healthPower_), currHealthPower(healthPower_) ,level(level_),fainted(false)
{
	//Living, constructed.
}				

//function to increase the health
void Living::increaseHealth(const int& hp){
	currHealthPower += hp;

	if(currHealthPower > (signed) maxHealthPower){
		currHealthPower = maxHealthPower;
	}

	return;
}

//function to reduce the health
void Living::reduceHealth(const int& damage){
	currHealthPower -= damage;

	if(currHealthPower < 0){
		currHealthPower = 0 ;
	}

	return;
}

Living::~Living(){

	//Living, destructed
}