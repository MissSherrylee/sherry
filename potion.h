#ifndef __POTION_H__
#define __POTION_H__

#include "textdisplay.h"
#include <string>
#include <iostream>

class Potion{
	int row,col;
	char symbol;
	std::string name;
	bool positive;
	bool reveal;

public:
	Potion(int,int,int);
	~Potion();

	int getRow();
	int getCol();
	std::string getName();	//	get the potion name
	int PotionEffect();	//	return 5 if the potion has positive effect; else return -5
	void notifyReveal();
	bool getReveal();

	void notifyDisplay(TextDisplay &);

};

#endif