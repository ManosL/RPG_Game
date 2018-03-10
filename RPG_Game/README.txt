Object Oriented Programming - Project

This Project was written by:

1) Emmanouil Lykos and,
2) Georgios Liakopoulos.

To compile this Project write on the terminal the
command "make".

To run this Project write on the terminal
the command "./RPG_Game".

To delete the object files and the executable file write
on the terminal the command "make clean".

Manual:

Warning: Make sure you have the CAPS LOCK button off.

->'w': Move up or Move up a choice at menus
->'a': Move left or Move down a choice at menus
->'s': Move down
->'d': Move right

->'i': Show Info about heroes
->'c': Check Hero Inventory
->'m': Show Map
->'q': Quit game or Quit Menu 


Hero:

    -The Hero can see anytime his info which includes
    name, level etc. and what armor wears and what weapons 
    hold.

    -In check inventory function the hero can see what has 
    in his inventory (not what armor wears or what weapons hold)
    and via this function the hero can Equip an Armor or Weapon,
    use a potion and Drom an Item or Spell.

    -In Equip function the replacing of a weapon or armor works
    automatically except for holding two one handed weapons.

Grid:

    -The initial values of heroes and monstersI have them defined 
    at Grid.cpp because we thought that it would be better modelization 
    to give externally of the heros' constructor their initial statistics.

    -When the Grid initializing we thought that it would be better
    to make the initial position of the heroes team the middle of 
    the grid because there are less possibilities to get trapped
    than putting him at some corner.

    -The "main" function of Grid is the Gameplay function.

    -We give to the heroes some immunity steps in the beginning
    of the game or when they lose a battle because after these
    situations need to reorganize themselves.

    -After moving from one square to another, if the square is not
    a market square, we take a rand() to determine if the heroes
    will battle with monster or monsters and we generate them.

Square:

    -We thought that it would be better to have a single class for square
    which includes 3 booleans and via them we can determine what type of 
    square is instead of having 3 classes. If the square has market we have
    a pointer which points to an object of type Market.

Market:

    -Has as building blocks a list of Items and a list of Spells.

    -The "main" function of the market class is the Interact function.

    -At interact function a hero will buy,sell or just see his inventory
    via a proper menu.    

    -When an item/spell is bought it stops to exist in the market

Battle System:
    -First is the heroes turn and then the monsters turn.

    -For each hero the player pick which monster to attack , each
    monster attack randomly to one alive hero.

    -Each hero has some options in every turn(attack,cast spell,
    use potion,change weapon , change armor , display statistics).
    Some of these options may not be valid , for example if the 
    hero has no spells and the player choose the option cast spell.
    In this case the system gives the opportunity to the player to 
    choose again between the above options.

    -The potions can be used only one time.

    -The potion can also be used at any time not only in battle.

    -The spells can be used only one time.

    -The damage of a weapon increases the strength of the hero when 
    the hero equips this weapon.The same for the armor.

    -The total armor is the sum of the initial armor of the hero ,the 
    body-armor ,the  hands-armor ,the body-armor and the legs-armor(if 
    the hero is equiped with armor-item in a part of his body).

    -Each spell that executed to a monster can faint this monster for some rounds.

    -The monster can be fainted with more than one spell. When the rounds of each 
    spell are finished the monster-statistic which was effected returns to its
    proper condition. 

    -The function useSpell is not a member-function of the class Hero because for
     each type of spell the function useSpell has to react with different way.


EXTRA

Generators:

    -You can go in the folder Project/generators and with the following commands to
     create other items and spells randomly(same names but different statistics):
     1.  g++ itemsGenerator.cpp
     2.  ./a.out
     3.  g++ spellGenerator.cpp
     4.  ./a.out
     5.  rm a.out	     

    -The generators create the statistics of each spell/item depending on the minimum
     level of the spell/item . For example a weapon with minimum level 1 can't have 
     very big damage.
     
