#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std ;


int main(void)
{

	list <string> PotionList ;
	list <string> WeaponList ;
	list <string> ArmorList  ;

	string name ;
	
	ifstream PotionFile;
 	PotionFile.open("potionNames.txt"); //open the potion-file
 	if (PotionFile.is_open()) 
 	{ 	 		
 		while ( !PotionFile.eof() ) //read one potion-name in every loop
 		{	
 			PotionFile >> name ; 
 			if ( !PotionFile.eof() )
 				PotionList.push_back(name);
 		}
 	}
 	PotionFile.close(); //close the potion-file

 	ifstream WeaponFile;
 	WeaponFile.open("weaponNames.txt"); //open the weapon-file
 	if (WeaponFile.is_open()) 
 	{ 	 		
 		while ( !WeaponFile.eof() ) //read one weapon-name in every loop
 		{	
 			WeaponFile >> name ; 
 			if ( !WeaponFile.eof() )
 				WeaponList.push_back(name);
 		}
 	}
 	WeaponFile.close(); //close the weapon-file

 	ifstream ArmorFile;
 	ArmorFile.open("armorNames.txt"); //open the potion-file
 	if (ArmorFile.is_open()) 
 	{ 	 		
 		while ( !ArmorFile.eof() ) //read one potion-name in every loop
 		{	
 			ArmorFile >> name ; 
 			if ( !ArmorFile.eof() )
 				ArmorList.push_back(name);
 		}
 	}
 	ArmorFile.close(); //close the potion-file

 	srand(time(NULL));

 	ofstream Items ("Items.txt") ;
 	if ( Items.is_open() )	//make the file with the items
 	{
 		Items << left << setw(20)  << "Name"; 
 		Items << left << setw(20)<< "Value" ; 
 		Items << left << setw(20)<< " Minimum Level" ;
 		Items << left << setw(20)<< "Type" ;
 		Items << left << setw(20)<< "Type Statistic 1 " ;
 		Items << left << setw(20) << "Type Statistic 2" << endl;
 		//start with weapons
 		for (list <string>::iterator it = WeaponList.begin() ; it != WeaponList.end() ; it++)
 		{									//statistics of weapons
 			int value = rand()%150 + 1 ;
 			int minLevel = rand()%10 + 1 ;
 			int dmg = rand()%30 + 1 ;
 			int oneHand = rand()%2 ;

 			Items << left << setw(20) << *it ;
 			Items << left << setw(20)<< minLevel*value ;
 			Items << left << setw(20)<< minLevel ;
 			Items << left << setw(20)<< "WEAPON" ; 
 			Items << left << setw(20)<< minLevel*dmg  ;
 			if (oneHand == 0)
 				Items << left << setw(20) << "FALSE" << endl ;
 			else
 				Items << left << setw(20) << "TRUE" << endl ; 
 		}

 		for (list <string>::iterator it = ArmorList.begin() ; it != ArmorList.end() ; it++)
 		{									//statistics of armors
 			int value = rand()%150 + 1 ;
 			int minLevel = rand()%10 + 1 ;
 			int def = rand()%30 + 1 ;
 			int part = rand()%4 ;

 			Items << left << setw(20) << *it ;  
 			Items << left << setw(20) << minLevel* value  ;
 			Items << left << setw(20) << minLevel ;
 			Items << left << setw(20) << "ARMOR" ; 
 			Items << left << setw(20) << minLevel* def ;
 			if (part == 0)
 				Items << left << setw(20)<< "HEAD" << endl ;
 			else if (part == 1)
 				Items << left << setw(20)<< "BODY" << endl ;
 			else if (part == 2)
 				Items << left << setw(20)<< "HANDS" << endl ;
 			else
 				Items << left << setw(20)<< "LEGS" << endl ; 
 		}

 		for (list <string>::iterator it = PotionList.begin() ; it != PotionList.end() ; it++)
 		{								//statistic of potions 
 			int value = rand()%100 + 1 ;
 			int minLevel = rand()%10 + 1 ;
 			int incr = rand()%10 + 1 ;
 			int stat = rand()%5 ;

 			Items << left << setw(20)<< *it ;
 			Items << left << setw(20)<< minLevel* value ;
 			Items << left << setw(20)<< minLevel ;
 			Items << left << setw(20)<< "POTION";
 			if (stat == 0)
 				Items << left << setw(20) << "HEALTH" ;
 			else if (stat == 1)
 				Items << left << setw(20) << "MAGIC"  ;
 			else if (stat == 2)
 				Items << left << setw(20) << "STRENGTH" ;
 			else if (stat == 3)
 				Items << left << setw(20)<< "DEXTERITY" ;
 			else 
 				Items << left << setw(20) << "AGILITY" ;

 			Items << left << setw(20) << minLevel* incr << endl; 

 		}

 	}

}