#ifndef __GOLD_H__
#define __GOLD_H__

#include "textdisplay.h"
#include <string>
#include <iostream>

class Gold{
	char symbol;
	int row,col,dragonX,dragonY;
	std::string type;
	int key;
	int value;
	bool canTake;
public:
	Gold(int,int,int);
	~Gold();

	int getRow();
	int getCol();
	int getDragonRow();
	int getDragonCol();
	int getKey();
	std::string getName();	//	get the type/name of the gold horde: small, normal, merchant, dragon
	int getValue();	//	get the horde value
	bool available();	//	return true if the gold is available to be picked up by the player now
	void addDragon(int,int);	//	add the dragon for the dragon horde
	void notifyAvailability();	//	when the dragon died, it will notify the dragon horde to change to be available
	void notifyDisplay(TextDisplay &);
};

#endif