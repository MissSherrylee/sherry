#include "potion.h"

Potion::Potion(int x, int y, int key){
	row = x;
	col = y;
	symbol = 'P';
	reveal = false;

	if(key >=0 && key <=2)	positive = true;
	else	positive = false;

	if(key == 0)	name = "RH";
	if(key == 1)	name = "BA";
	if(key == 2)	name = "BD";
	if(key == 3)	name = "PH";
	if(key == 4)	name = "WA";
	if(key == 5)	name = "WD";

}

Potion::~Potion(){}

std::string Potion::getName(){	return name;}

int Potion::getRow(){
	return row;
}

int Potion::getCol(){
	return col;
}

int Potion::PotionEffect(){
	symbol = '.';	//	the potion has been taken and used by the player

	if(positive){	
		if(name == "RH")	return 10;
		else	return 5;
	}
	else{
		if(name == "PH")	return -10;
		else return -5;
	}
}

bool Potion::getReveal(){
	return reveal;
}

void Potion::notifyReveal(){
	reveal = true;
}

void Potion::notifyDisplay(TextDisplay &td){
	td.notify(row,col,symbol);
}
