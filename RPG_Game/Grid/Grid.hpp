#ifndef __GRID__
#define __GRID__

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "../Living/Living.hpp"

class Grid{

private:
	class Square{

	private:
		class Market{

		public:
			std::list<Item*> Items;
			std::list<Spell*> Spells;

			Market(const std::list<Item*>&,const std::list<Spell*>&);

			void give(std::list<Item*>::iterator&);
			void give(std::list<Spell*>::iterator&);

			void Interact(const int&,Hero**&);

			void get(std::list<Item*>::iterator&);
			void get(std::list<Spell*>::iterator&);

			~Market();
		};

	public:
		const bool isAccessible;
		const bool hasMarket;
		const bool isCommon;
		Market* market;      //= NULL if it isn't a market square

		Square(const bool&,const bool&,const bool&);				 //constructor if the square doesn't have Market
		Square(const bool&,const bool&,const bool&,const std::list<Item*>&,const std::list<Spell*>&); //constructor if the square has market

		Market*& getMarket(){ return market; }
		const bool& isMarketSquare() const{ return hasMarket; }
		const bool& isAccessibleSquare() const{ return isAccessible; }
		const bool& isCommonSquare() const{ return isCommon; }

		~Square();
	};

	Square*** grid;
	const size_t width;	
	const size_t height;
	Hero** heroes;
	const int no_of_heroes;

public:

	Grid(const size_t&,const size_t&,const int&,const std::list<Item*>&,const std::list<Spell*>&,const std::vector<std::string>&,const std::vector<HeroClass>&);

	void GamePlay();        
	void displayMap() const;

	~Grid();
};

#endif