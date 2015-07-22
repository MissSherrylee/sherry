#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "textdisplay.h"
#include <string>
#include <iostream>

class Player{
	int row,col;
	int Atk, Def, HP;
	double gold;
	std::string race;
	bool isDead;
	char symbol;

	int maxHP;

public:
	Player(int,int,std::string);	//	create a player object by consuming a character representing the race
	~Player();

	int getAtk();	//	get the atk of the player

	int getDef();	//	get the def of the player

	int getHP();	//	get the HP of the player

	std::string getRace();	//	get the race name of the player 
	double getGold();	//	get number of gold of the player

	bool CharDead();	//	return true if the player's HP is 0

	void notify(int);	//	notify the player that it has been attacked by <int> damages

	void restoreStat();	//	restore the Atk and Def back to initial state in new floor
	void addGold();
	void addGold(int);
	void addHP(int);
	void addAtk(int);
	void addDef(int);
	void setCoord(int,int);
	void notifyDisplay(TextDisplay &td);
	
};


#endif