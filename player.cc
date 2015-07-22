#include "player.h"
#include <cmath>

Player::Player(int x, int y, std::string ch){
	row = x;
	col = y;

	symbol = '@';
	isDead = false;
	gold = 0;

	if(ch == "h"){
		race = "Human";

		Atk = 20;
		Def = 20;
		HP = 140;
	}

	if(ch == "e"){
		race = "Elves";

		Atk = 30;
		Def = 10;
		HP = 140;
	}

	if(ch == "d"){
		race = "Dwarf";

		Atk = 20;
		Def = 30;
		HP = 100;
	}

	if(ch == "o"){
		race = "Orc";

		Atk = 30;
		Def = 25;
		HP = 180;
	}

	maxHP = HP;
}

Player::~Player(){}

int Player::getAtk(){
	return Atk;
}

int Player::getDef(){
	return Def;
}

int Player::getHP(){
	return HP;
}

std::string Player::getRace(){
	return race;
}

double Player::getGold(){

	return gold;
}

bool Player::CharDead(){
	return isDead;
}

void Player::notify(int damage){
	HP -= damage;

	if(HP <= 0){
		isDead = true;
		HP = 0;
		symbol = '.';
	}
}

void Player::addGold(){
	gold++;
}

void Player::addGold(int amt){
	gold += amt;
}

void Player::restoreStat(){
	if(race == "Human"){

		Atk = 20;
		Def = 20;
	}

	if(race == "Elves"){

		Atk = 30;
		Def = 10;
	}

	if(race == "Dwarf"){

		Atk = 20;
		Def = 30;
	}

	if(	race == "Orc"){

		Atk = 30;
		Def = 25;
	}
}

void Player::addHP(int amt){
	HP += amt;

	if(HP > maxHP)	HP = maxHP;
	if(HP < 0){
		HP = 0;
		isDead = true;
	}
}

void Player::addAtk(int amt){
	Atk += amt;
}

void Player::addDef(int amt){
	Def += amt;
}

void Player::setCoord(int x, int y){
	row = x;
	col = y;
}

void Player::notifyDisplay(TextDisplay &td){
	td.notify(row,col,symbol);
}
