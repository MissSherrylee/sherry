#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "textdisplay.h"
#include <string>
#include <iostream>

class Enemy{
	int row,col;
	int Atk, Def, HP;
	int maxAtk;
	int life;
	char symbol;
	bool isDead;
	bool hostile;
	bool attemptToAttack;

public:
	Enemy(int,int,char);
	~Enemy();

	int getAtk();	//	get the atk of the enemy
	int getMaxAtk();

	int getDef();	//	get the def of the enemy

	int getHP();	//	get the HP of the enemy

	int getRow();
	int getCol();

	char getSymbol();

	bool CharDead();	//	return true if the enemy's HP is 0
	bool EnemyHostile();	//	return true if the enemy is hostile to the player
	bool EnemyattemptToAttack();	//	return true if the enemy is ready to attack the player in next move

	void notifyMerchantHostility();
	void notify(int);	//	notify the Enemy that it has been attacked by <int> damages
	bool watchNeighbourAttack(TextDisplay &);	
	void setCoord(int,int);
	void notifyDisplay(TextDisplay &td);
	void setZeroDef();

};

#endif