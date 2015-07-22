#include "enemy.h"
#include <cstdlib>
#include <cmath>

Enemy::Enemy(int x, int y, char ch){
	row = x;
	col = y;
	symbol = ch;
	maxAtk = 0;
	life = 1;
	isDead = false;
	hostile = true;
	attemptToAttack = false;

	if(symbol == 'V'){
		Atk = 25;
		Def = 25;
		HP = 50;
	}

	if(symbol == 'W'){
		Atk = 30;
		maxAtk = 50;
		Def = 5;
		HP = 120;
	}

	if(symbol == 'T'){
		Atk = 25;
		Def = 15;
		HP = 120;
	}

	if(symbol == 'N'){
		Atk = 5;
		Def = 10;
		HP = 70;
	}

	if(symbol == 'M'){
		Atk = 70;
		Def = 5;
		HP = 30;

		hostile = false;
	}

	if(symbol == 'X'){
		Atk = 35;
		Def = 20;
		HP = 50;
		life = 2;
	}
}

Enemy::~Enemy(){}

int Enemy::getAtk(){ return Atk;}
int Enemy::getDef(){ return Def;}
int Enemy::getHP(){ return HP;}
int Enemy::getRow(){ return row;}
int Enemy::getCol(){ return col;}
int Enemy::getMaxAtk(){ return maxAtk;};

char Enemy::getSymbol(){
	return symbol;
}

bool Enemy::CharDead(){ return isDead;}
bool Enemy::EnemyHostile(){ return hostile;}
bool Enemy::EnemyattemptToAttack(){ return attemptToAttack;}

void Enemy::notifyMerchantHostility(){
	if(symbol == 'M')	hostile = true;
}

void Enemy::notify(int damage){

	HP -= damage;

	hostile = true;
	attemptToAttack = true;

	if(HP <= 0){
		life--;
		
		if(life <= 0){
			HP = 0;
			isDead = true;
			hostile = false;
			attemptToAttack = false;
			symbol = '.';
		}
		else{

			HP = 50;
			isDead = false;
			hostile = true;
			attemptToAttack = true;
		}
		
	}
}

bool Enemy::watchNeighbourAttack(TextDisplay &td){
	
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
		
		attemptToAttack = false;
		return false;
	}

	return false;
}

void Enemy::setCoord(int x, int y){
	row = x;
	col = y;
}

void Enemy::notifyDisplay(TextDisplay &td){
	td.notify(row,col,symbol);
}

void Enemy::setZeroDef(){
	Def = 0;
}

