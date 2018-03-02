RPG_Game: main.o Grid.o Market.o Square.o Item.o Hero.o Living.o Monster.o Ready.o Spells.o BattleArena.o
	g++ -g main.o Grid.o Market.o Square.o Item.o Hero.o Living.o Monster.o Ready.o Spells.o BattleArena.o -o RPG_Game -Wall

main.o: ./Main/main.cpp
	g++ -c ./Main/main.cpp

Grid.o: ./Grid/Grid.cpp
	g++ -c ./Grid/Grid.cpp

Market.o: ./Grid/Market.cpp
	g++ -c 	./Grid/Market.cpp

Square.o: ./Grid/Square.cpp
	g++ -c ./Grid/Square.cpp

Item.o: ./Item/Item.cpp
	g++ -c ./Item/Item.cpp

Hero.o: ./Living/Hero.cpp
	g++ -c ./Living/Hero.cpp

Living.o: ./Living/Living.cpp
	g++ -c ./Living/Living.cpp

Monster.o: ./Living/Monster.cpp
	g++ -c ./Living/Monster.cpp

Ready.o: ./Ready/Ready.cpp
	g++ -c ./Ready/Ready.cpp

Spells.o: ./Spell/Spells.cpp
	g++ -c ./Spell/Spells.cpp	

BattleArena.o: ./BattleArena/BattleArena.cpp
	g++ -c ./BattleArena/BattleArena.cpp	

.PHONY: clean

clean:
	rm -rf 	main.o Grid.o Market.o Square.o Item.o Hero.o Living.o Monster.o Ready.o Spells.o BattleArena.o RPG_Game					
