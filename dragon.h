#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "textdisplay.h"
#include <string>
#include <iostream>

class Dragon{
	int row,col;
	int goldRow,goldCol;
	char symbol;
	int Atk, Def, HP;
	bool isDead;
	bool hostile;
	bool attemptToAttack;
public:
	Dragon(int,int);
	~Dragon();

	void notifyHostility(bool);	//	the dragon horde will notify the dragon to become hostile if the player is 1 radius beside the dragon horde
	void notify(int);	//	the player notify the dragon that it is attacked by "int" damages;
						//	if the dragon died, it should notify its dragon horde to become available for being picked up
	int getRow();
	int getCol();
	int getAtk();
	int getDef();
	int getHP();
	int getGoldRow();
	int getGoldCol();
	char getSymbol();
	bool CharDead();
	bool EnemyHostile();
	bool EnemyattemptToAttack();
	bool watchNeighbourAttack(TextDisplay &td);
	void setGoldRowCol(int,int);

	void setCoord(int,int);
	void notifyDisplay(TextDisplay &td);

};


#endif