#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std ;

int main(void)
{
	list <string> SpellNameList  ;

	string name ;
	
	ifstream SpellFile;
 	SpellFile.open("spellNames.txt"); //open the spell-file
 	if (SpellFile.is_open()) 
 	{ 	 		
 		while ( !SpellFile.eof() ) //read one spell-name in every loop
 		{	
 			SpellFile >> name ; 
 			if ( !SpellFile.eof() )
 				SpellNameList.push_back(name);
 		}
 	}
 	SpellFile.close(); //close the spell-file

 	srand(time(NULL));

 	ofstream Spells ("Spells.txt") ;
 	if ( Spells.is_open() )	//make the spell file
 	{
 		Spells << left << setw(20) << "Name"; 
 		Spells << left << setw(10)<< "Price" ; 
 		Spells << left << setw(20)<< "Minimum Level" ;
 		Spells << left << setw(20)<< "Minimum damage" ;
 		Spells << left << setw(20)<< "Maximum damage" ;
 		Spells << left << setw(10)<< "Magic" ;
 		Spells << left << setw(10)<< "Rounds";
 		Spells << left << setw(15)<< "Spell Type" ;
 		Spells << left << setw(20)<<"Reduce Rate " << endl;

 		for (list<string>::iterator it = SpellNameList.begin() ; it != SpellNameList.end() ; it++)
 		{									//spell statistics
 			int price = rand()%100 + 1;
 			int min_Level = rand()%10 + 1;
 			int dmg = rand()%20 + 1 ;
 			int magic = rand()%20 + 1;
 			int round_duration = rand()%4 + 1;
 			int spell_type = rand()%3;
 			double reduce_rate = (double)rand()/(double)RAND_MAX ;

 			int min_dmg = dmg ;
 			int max_dmg = dmg + 5;
 			
 			Spells << left << setw(20)<< *it ;
 			Spells << left << setw(10)<< min_Level* price ;
 			Spells << left << setw(20)<< min_Level ;
 			Spells << left << setw(20)<< min_Level* min_dmg ;
 			Spells << left << setw(20)<< min_Level* max_dmg ;
 			Spells << left << setw(10)<< min_Level* magic ;
 			Spells << left << setw(10)<< round_duration;
 		
 			if (spell_type == 0 )
 				Spells << left << setw(15) << "ICE" ;
 			else if (spell_type == 1)
 				Spells << left << setw(15) << "FIRE" ;
 			else
 				Spells << left << setw(15) << "LIGHTING";

 			Spells << left << setw(20)<< reduce_rate << endl;

 		}
 	}

}