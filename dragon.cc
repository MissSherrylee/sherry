#include "dragon.h"
#include <cmath>

Dragon::Dragon(int x,int y){
	row = x;
	col = y;
	symbol = 'D';
	isDead = false;
	hostile = false;
	attemptToAttack = false;
	
	Atk = 20;
	Def = 20;
	HP = 150;
}

Dragon::~Dragon(){}

void Dragon::notify(int damage){
	HP -= damage;

	hostile = true;
	attemptToAttack = true;

	if(HP <= 0){
		HP = 0;
		isDead = true;
		hostile = false;
		attemptToAttack = false;
		symbol = '.';
	}
}

void Dragon::notifyHostility(bool foundPlayer){
	hostile = foundPlayer;
}

int Dragon::getRow(){
	return row;
}

int Dragon::getCol(){
	return col;
}

int Dragon::getAtk(){
	return Atk;
}

int Dragon::getDef(){
	return Def;
}

int Dragon::getHP(){
	return HP;
}

int Dragon::getGoldRow(){
	return goldRow;
}

int Dragon::getGoldCol(){
	return goldCol;
}

char Dragon::getSymbol(){
	return symbol;
}

bool Dragon::CharDead(){
	return isDead;
}

bool Dragon::EnemyHostile(){
	return hostile;
}

bool Dragon::EnemyattemptToAttack(){
	return attemptToAttack;
}

bool Dragon::watchNeighbourAttack(TextDisplay &td){
	
	if(hostile){

		if(td.getSymbol(row-1,col-1) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		if(td.getSymbol(row-1,col) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		if(td.getSymbol(row-1,col+1) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		if(td.getSymbol(row,col-1) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		if(td.getSymbol(row,col+1) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		if(td.getSymbol(row+1,col-1) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		if(td.getSymbol(row+1,col) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		if(td.getSymbol(row+1,col+1) == '@'){

			if(!attemptToAttack){
				attemptToAttack = true;
				return false;
			}

			else{
				return true;
			}
		}

		return false;
	}

	return false;
}

void Dragon::setGoldRowCol(int x, int y){
	goldRow = x;
	goldCol = y;
}

void Dragon::setCoord(int x, int y){
	row = x;
	col = y;
}

void Dragon::notifyDisplay(TextDisplay &td){
	td.notify(row,col,symbol);
}