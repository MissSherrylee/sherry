#include "gold.h"

Gold::Gold(int x, int y,int key){
	symbol = 'G';
	row = x;
	col = y;
	this->key = key;
	canTake = true;

	if(key == 0){
		type = "normal";
		value = 1;
	}
	if(key == 1){
		type = "small";
		value = 2;
	}
	if(key == 2){
		type = "Dragon";
		value = 6;
		canTake = false;
	}
	if(key == 3){
		type = "Merchant";
		value = 4;
	}
}

Gold::~Gold(){}

std::string Gold::getName(){
	return type;
}

int Gold::getRow(){
	return row;
}

int Gold::getCol(){
	return col;
}

int Gold::getValue(){
	symbol = '.';
	return value;
}

int Gold::getDragonRow(){
	return dragonX;
}

int Gold::getDragonCol(){
	return dragonY;
}

int Gold::getKey(){
	return key;
}

bool Gold::available(){
	return canTake;
}

void Gold::addDragon(int dX,int dY){
	dragonX = dX;
	dragonY = dY;
}

void Gold::notifyAvailability(){
	canTake = true;
}

void Gold::notifyDisplay(TextDisplay &td){
	td.notify(row,col,symbol);
}

