#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include "GameBoard.h"

GameBoard::GameBoard(){
	prev = '.';
	level = 1;
	score = 0;
	enemyindex = 0;
	goldindex = 0;
	dragonindex = 0;
	potionindex = 0;
	gameStart = false;

	std::string line;
	std::ostringstream os;
	filename = "floor";

	int num = rand()%3;
	os << num;

	filename = filename.append(os.str());


	std::string file = filename;
	file.append(".txt");

	std::ifstream myfile (file.c_str());

	if(myfile.is_open()){
		
		td = new TextDisplay(file);
		myfile.close();

	}

	revealist[0] = "RH";
	revealist[1] = "BA";
	revealist[2] = "BD";
	revealist[3] = "PH";
	revealist[4] = "WA";
	revealist[5] = "WD";
}

GameBoard::~GameBoard(){

	delete td;

	delete p;

}


void GameBoard::MovePlayer(std::string &s){
	//get destination.
	int temp_x, temp_y;
	std::string direction;
	
	if(s=="no"){
		temp_x = px-1;
		temp_y = py;

		direction = "north";

	}
	if(s=="so"){
		temp_x = px+1;
		temp_y = py;

		direction = "south";
	}
	if(s=="ea"){
		temp_x = px;
		temp_y = py+1;

		direction = "east";
	}
	if(s=="we"){
		temp_x = px;
		temp_y = py-1;

		direction = "west";
	}
	if(s=="ne"){
		temp_x = px-1;
		temp_y = py+1;

		direction = "north-east";
	}
	if(s=="nw"){
		temp_x = px-1;
		temp_y = py-1;

		direction = "north-west";
	}
	if(s=="se"){
		temp_x = px+1;
		temp_y = py+1;

		direction = "south-east";
	}
	if(s=="sw"){
		temp_x = px+1;
		temp_y = py-1;

		direction = "south-west";
	}

	//start moving
	char e = td->getSymbol(temp_x,temp_y); //symbol in destination.

	if(e == '.' || e == '+' || e == '#'){

		p->setCoord(temp_x,temp_y);
		td->notify(px,py,prev);

		prev = td->getSymbol(temp_x,temp_y);
		px = temp_x;
		py = temp_y;

		p->notifyDisplay(*td);

		ActionMessage = "Player moves to the " + direction + ". "; 
		
	}

	else if(e == '/'){
		level++;

		p->setCoord(temp_x,temp_y);
		td->notify(px,py,prev);

		px = temp_x;
		py = temp_y;

		p->notifyDisplay(*td);

		if(level <=5){
			clearStat();
			toNewLevel();

			prev = '.';

			ActionMessage = "Player moves to the " + direction + ". "; 

			ActionMessage += "Player goes to the floor " + getStrLevel() + ". ";
		}

	}

	else if(e == 'G'){

		Gold *g = getHorde(temp_x,temp_y);
		
		if(g->available()){ 

			p->addGold(g->getValue());
			p->setCoord(temp_x,temp_y);
			td->notify(px,py,prev);

			prev = '.';
			px = temp_x;
			py = temp_y;

			p->notifyDisplay(*td);

			std::ostringstream os;
			os << g->getValue();

			ActionMessage = "Player moves to the " + direction + " and get " + os.str() + " golds. ";
		}
	}

	else{
		std::cerr<<"wrong move!"<<std::endl;
	}

	if(level <=5){
		WatchMessage(px,py);

		MoveEnemy();
	}
}

void GameBoard::WatchMessage(int x, int y){

	if(td->getSymbol(x-1,y-1) == 'P'){
		Potion *po = getPotion(x-1,y-1);

		if(po->getReveal()){

			std::cout << po->getName() << std::endl;
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}

	if(td->getSymbol(x-1,y) == 'P'){
		Potion *po = getPotion(x-1,y);

		if(po->getReveal()){
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}

	if(td->getSymbol(x-1,y+1) == 'P'){
		Potion *po = getPotion(x-1,y+1);

		if(po->getReveal()){
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}

	if(td->getSymbol(x,y-1) == 'P'){
		Potion *po = getPotion(x,y-1);

		if(po->getReveal()){
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}

	if(td->getSymbol(x,y+1) == 'P'){
		Potion *po = getPotion(x-1,y+1);

		if(po->getReveal()){
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}

	if(td->getSymbol(x+1,y-1) == 'P'){
		Potion *po = getPotion(x+1,y-1);

		if(po->getReveal()){
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}

	if(td->getSymbol(x+1,y) == 'P'){
		Potion *po = getPotion(x+1,y);

		if(po->getReveal()){
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}

	if(td->getSymbol(x+1,y+1) == 'P'){
		Potion *po = getPotion(x+1,y+1);

		if(po->getReveal()){
			ActionMessage += "Player sees a " + po->getName() + " potion. ";
		}
		else{
			ActionMessage += "Player sees an unknown potion. ";
		}
	}
}

void GameBoard::clearStat(){
	prev = '.';

	p->restoreStat();
	enemyindex = 0;
	goldindex = 0;
	potionindex = 0;
	dragonindex = 0;


}

void GameBoard::toNewLevel(){

	std::ifstream myfile;
	std::string file = filename;
	std::string file2 = filename;
	file.append(".txt");

	myfile.open(file.c_str());

	td = new TextDisplay(file);

	myfile.close();

	//	put player
	std::ostringstream os;
	std::string line;
	int row, col;
	room = rand()%4;
	os << room;
	int num;

 	file2.append(os.str()+".txt");

	myfile.open(file2.c_str());

	getline(myfile,line);
	std::istringstream	(line) >> num;//get the numbers of coordinates in file.

	num = rand()%num;

	for(int i=0;i<=num;i++){
		getline(myfile,line);
	}
	std::istringstream	(line) >> row >> col;

	p->setCoord(row,col);

	px = row;
	py = col;

	p->notifyDisplay(*td);

	myfile.close();



	//	generate stair, enemies, potion, gold
	this->setBoard();
}

void GameBoard::UseItem(std::string &s){
	char itemSymbol;
	int temp_x,temp_y;

	if(s == "no")	{
		temp_x = px-1;
		temp_y = py;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "so")	{
		temp_x = px+1;
		temp_y = py;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "we")	{
		temp_x = px;
		temp_y = py-1;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "ea")	{
		temp_x = px;
		temp_y = py+1;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "ne")	{
		temp_x = px-1;
		temp_y = py+1;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "nw")	{
		temp_x = px-1;
		temp_y = py-1;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "se")	{
		temp_x = px+1;
		temp_y = py+1;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "sw")	{
		temp_x = px+1;
		temp_y = py-1;
		itemSymbol = td->getSymbol(temp_x,temp_y);
	}


	if(itemSymbol == 'P'){
		Potion *po = getPotion(temp_x,temp_y);

		ActionMessage = "Player uses the potion " + po->getName() + ". ";
		
		notifyTakePotion(po);
		
		po->notifyDisplay(*td);

		for(int i = 0; i < 10; i++){
			if(plist[i]->getName() == po->getName()){
				plist[i]->notifyReveal();
			}
		}

		for(int i = 0; i < 6; i++){
			if(revealist[i] == po->getName()){
				revealist[i] = "X";
				break;
			}
		}
		
	}
	else{
		std::cerr << "Invalid command." << std::endl;
	}

	MoveEnemy();

}

void GameBoard::notifyTakePotion(Potion *cl){
	if(cl->getName() == "RH"){
		p->addHP(cl->PotionEffect());
	}
	if(cl->getName() == "BA"){
		p->addAtk(cl->PotionEffect());
	}
	if(cl->getName() == "BD"){
		p->addDef(cl->PotionEffect());
	}
	if(cl->getName() == "PH"){
		if(p->getRace() == "Elves"){
			p->addHP(-cl->PotionEffect());
		}
		else{
			p->addHP(cl->PotionEffect());
		}
	}
	if(cl->getName() == "WA"){
		if(p->getRace() == "Elves"){
			p->addAtk(-cl->PotionEffect());
		}
		else{
			p->addAtk(cl->PotionEffect());
		}
	}
	if(cl->getName() == "WD"){
		if(p->getRace() == "Elves"){
			p->addDef(-cl->PotionEffect());
		}
		else{
			p->addDef(cl->PotionEffect());
		}
	}
}

void GameBoard::AttackEnemy(std::string &s){
	char enemySymbol;
	int temp_x,temp_y;

	if(s == "no")	{
		
		temp_x = px-1;
		temp_y = py;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "so")	{

		temp_x = px+1;
		temp_y = py;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "we")	{
		
		temp_x = px;
		temp_y = py-1;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "ea")	{
	
		temp_x = px;
		temp_y = py+1;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "ne")	{
		
		temp_x = px-1;
		temp_y = py+1;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "nw")	{
		
		temp_x = px-1;
		temp_y = py-1;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "se")	{
		
		temp_x = px+1;
		temp_y = py+1;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}

	if(s == "sw")	{
		
		temp_x = px+1;
		temp_y = py-1;
		enemySymbol = td->getSymbol(temp_x,temp_y);
	}


	if(enemySymbol == 'V' || enemySymbol == 'W' || enemySymbol == 'T' || enemySymbol == 'N' || enemySymbol == 'M' || enemySymbol == 'X'){

		Enemy *en = getEnemy(temp_x,temp_y);
		
		if(enemySymbol == 'M'){
			
			for(int i = 0; i < 20; i++){	//	notify all living Merchants' hostility if the enemy the player attacked is a merchant
				if(!elist[i]->CharDead()){
					elist[i]->notifyMerchantHostility();
				}
			}
		}

		//	begin fight
		double i = en->getDef();
		double j = p->getAtk();

		std::cout << i << " " << std::endl;
		double damage = ceil((100/(100+i)))*j;

		int recover = rand()%3;

		if(enemySymbol == 'V' && recover == 2){
			damage = damage * 0.9;	//	recover 10% damage for vampire
		}

		en->notify(damage);

		if(en->CharDead()){
			if(en->getSymbol() != 'D' && en->getSymbol() != 'M'){
				p->addGold();
			}
		}

		//	end fight


		if(en->CharDead()){

			if(enemySymbol == 'M'){	//	if the Merchant died, drop a gold of value 4
				
				glist[goldindex] = new Gold(temp_x,temp_y,3);
				glist[goldindex]->notifyDisplay(*td);
				goldindex++;
			}
			else{
				en->notifyDisplay(*td);
			}

			ActionMessage = "The enemy has been slained!";

		}
		else{

			std::ostringstream os;
			os << damage;

			ActionMessage = "Player deals " + os.str() + " damages to ";

			std::ostringstream os2;
			os2 << en->getSymbol();

			ActionMessage += os2.str() + "( ";

			std::ostringstream os3;	
			os3 << en->getHP();

			ActionMessage += os3.str() + "). ";
		}	
	}

	else if(enemySymbol == 'D'){
		Dragon *dg = getDragon(temp_x,temp_y);

		//	begin fight
		double i = dg->getDef();
		double j = p->getAtk();
		double damage = ceil((100/(100+i))) * j;

		dg->notify(damage);

		//	end fight

		ActionMessage = "Player deals ";

		std::ostringstream os;
		os << damage;

		ActionMessage += os.str() + " damages to D(";

		std::ostringstream oss;	
		oss << dg->getHP();

		ActionMessage += oss.str() + "). ";

		if(dg->CharDead()){
			dg->notifyDisplay(*td);

			Gold *dragonHorde = getHorde(dg->getGoldRow(),dg->getGoldCol());
			std::cout << dg->getGoldCol() << " " <<dg->getGoldRow();
			dragonHorde->notifyAvailability();

		}	

	}

	else{
		std::cerr << "The target you want to attack is not an enemy." << std::endl;
	}

	MoveEnemy();	//	include watchNeighbour
}

void GameBoard::MoveEnemy(){

	if(enemyindex >= 20){
		enemyindex = 0;
	}
	

		if(!elist[enemyindex]->CharDead()){

			if(!elist[enemyindex]->EnemyattemptToAttack()){

				int currentX = elist[enemyindex]->getRow();
				int currentY = elist[enemyindex]->getCol();

				bool allNeighoubourfilled = false;

				if(td->getSymbol(currentX-1,currentY-1) != '.' &&
					td->getSymbol(currentX-1,currentY) != '.' &&
					td->getSymbol(currentX-1,currentY+1) != '.' &&
					td->getSymbol(currentX,currentY-1) != '.' &&
					td->getSymbol(currentX,currentY+1) != '.' &&
					td->getSymbol(currentX+1,currentY-1) != '.' &&
					td->getSymbol(currentX+1,currentY) != '.' &&
					td->getSymbol(currentX+1,currentY+1) != '.'){

					allNeighoubourfilled = true;
				}

				if(!allNeighoubourfilled){

					bool foundplace = false;

					while(!foundplace){
						int newX = rand()%3+(currentX-1);
						int newY = rand()%3+(currentY-1);

						if(td->getSymbol(newX,newY) == '.'){

							td->notify(elist[enemyindex]->getRow(),elist[enemyindex]->getCol(),'.');
							elist[enemyindex]->setCoord(newX,newY);
							elist[enemyindex]->notifyDisplay(*td);

							foundplace = true;
						}
					}
				}

			}	
	
		}

		enemyindex++;
	//	the enemy watches its neighbours and attacks the player if the player is 1 radius around it
	for(int i = 0; i < 20; i++){
		if(!elist[i]->CharDead()){
			if(elist[i]->watchNeighbourAttack(*td)){

				int miss = rand()%2;
				int Tchance = rand()%50;
				double damage;

				if(miss==0)	damage = 0;
				else{
					double x = p->getDef();
					double y;

					if(elist[i]->getSymbol() == 'W' && elist[i]->getHP() < 24){
						y = elist[i]->getMaxAtk();
						elist[i]->setZeroDef();
					}

					else{
						y = elist[i]->getAtk();
					
					}

					damage = ceil((100/(100+x))) * y;

					if(elist[i]->getSymbol() == 'T' && Tchance == 1){

						damage += 10;
					}
				}

				p->notify(damage);

				std::ostringstream os;
				os << elist[i]->getSymbol();

				ActionMessage += os.str() + " deals ";

				std::ostringstream os2;
				os2 << damage;

				ActionMessage += os2.str() + " damages to the Player. ";
			}
		}
	}

	//	dragon fight
	for(int i = 0; i < dragonindex ; i++){

		if(!dlist[i]->CharDead()){
			if(dlist[i]->watchNeighbourAttack(*td)){

				int miss = rand()%2;
				double damage;

				if(miss==0)	damage = 0;
				else{
					double x = p->getDef();
					double y = dlist[i]->getAtk();
					damage = ceil((100/(100+x))) * y;
				}

				p->notify(damage);

				std::ostringstream os;

				ActionMessage +=  "D deals ";

				os << damage;

				ActionMessage += os.str() + " damages to the Player. ";
			}
		}
	}

	//	dragonhorde "watch"
	for(int i = 0; i < goldindex; i++){
		if(glist[i]->getKey() == 2){
			DragonHordeObserve(glist[i]);
		}
	}

}

bool GameBoard::isDead(){
	return p->CharDead();
}

void GameBoard::SelectRace(std::string &r){
	std::ostringstream os;
	std::string file = filename;
	std::string line;
	int row, col;
	room = rand()%4;
	os << room;
	int num;

	file.append(os.str()+".txt");
	
	std::ifstream myfile;
	myfile.open(file.c_str());

	getline(myfile,line);
	std::istringstream	(line) >> num;//get the numbers of coordinates in file.

	num = rand()%num;

	for(int i=0;i<=num;i++){
		getline(myfile,line);
	}
	std::istringstream	(line) >> row >> col;

	p = new Player(row,col,r);

	// current player position
	px = row;
	py = col;
	prev = '.';

	p->notifyDisplay(*td);

	ActionMessage = "Player has spawned.";

	myfile.close();

	gameStart = true;
}

void GameBoard::setStair(){
	std::ostringstream os;
	std::string line;
	std::string file = filename;
	int row, col;
	int num = rand()%4;
	
	while(num == room){
		num = rand()%4;
	}

	os << num;

	file.append(os.str()+".txt");

	std::ifstream myfile;
	

	myfile.open(file.c_str());

	getline(myfile,line);

	std::istringstream (line) >> num;

	num = rand()%num;


	for(int i=0; i<=num; i++){
		getline(myfile,line);
	}

	std::istringstream(line) >> row >>col;
	td->notify(row,col,'/');

	myfile.close();
}

//helper function of select gold and potion
void GameBoard::setItem(int n, int index){
	std::ostringstream os;
	std::string line;
	std::string file = filename;
	std::ifstream myfile;
	int room = rand()%5;
	int row, col;
	int key;
	int num;//num used to record every random number needed in this method.
	
	os << room;
	file.append(os.str()+".txt");
	
	key = rand()%n;//random select poison.

	myfile.open(file.c_str());

	getline(myfile,line);
	std::istringstream	(line) >> num;
	num = rand()%num;

	for(int i=0; i<=num; i++){
		getline(myfile,line);
	}
	
	std::istringstream	(line) >> row >> col;
	
	if(td->getSymbol(row,col) != '.'){
		setItem(n,index);
	}
	
	else {
		if(n == 6){
			bool reveal = false;

			plist[index] = new Potion(row,col,key);

			for(int i = 0; i < 10; i++){
				if(plist[index]->getName() != revealist[i]) reveal = true;
				else{	
					reveal = false;
					break;
				}
			}

			if(reveal)	plist[index]->notifyReveal();

			plist[index]->notifyDisplay(*td);
			potionindex++;
		}
		else{


			if(key >= 0 && key <= 4){
				key = 0;
			}
			else if(key >= 5 && key <= 6){
				key = 1;
			}
			else	key = 2;

			glist[index] = new Gold(row,col,key);
			
			if(key == 2){
				bool foundplace = false;
				
				while(!foundplace){
					int dragonX = rand()%3+(row-1);
					int dragonY = rand()%3+(col-1);

					if(td->getSymbol(dragonX,dragonY) == '.'){

						foundplace = true;

						dlist[dragonindex] = new Dragon(dragonX,dragonY);
						
						glist[index]->addDragon(dragonX,dragonY);

						dlist[dragonindex]->notifyDisplay(*td);
						dlist[dragonindex]->setGoldRowCol(row,col);

						dragonindex++;
					}
				}
			}
			goldindex++;
			glist[index]->notifyDisplay(*td);
		}
	}

	myfile.close();
}

void GameBoard::setEnemies(int index){
	char symbol;
	int rand_room;
	int rand_num = rand()% 18;
	int num;
	int row,col;
	std::ostringstream os;
	std::string file = filename;
	std::ifstream myfile;
	std::string line;

	rand_room = rand()% 5;
	os << rand_room;

	file.append(os.str()+".txt");
	
	myfile.open(file.c_str());
	
	getline(myfile,line);

	std::istringstream (line) >> num;	//	get total number of coordinates

	num = rand()%num;

	for(int i = 0; i <= num; i++){
		getline(myfile,line);
	}

	std::istringstream(line) >> row >> col;
	
	if(td->getSymbol(row,col) != '.'){
		setEnemies(index);
	}
	else{

		if(rand_num >= 0 && rand_num <=2){
			symbol = 'V';

			elist[index] = new Enemy(row,col,symbol);

			elist[index]->notifyDisplay(*td);
		}
		else if(rand_num >= 3 && rand_num <= 6){
			symbol = 'W';
			elist[index] = new Enemy(row,col,symbol);

			elist[index]->notifyDisplay(*td);
		}
		else if(rand_num >= 7 && rand_num <= 8){
			symbol = 'T';
			elist[index] = new Enemy(row,col,symbol);

			elist[index]->notifyDisplay(*td);
		}
		else if(rand_num >= 9 && rand_num <= 13){
			symbol = 'N';
			elist[index] = new Enemy(row,col,symbol);

			elist[index]->notifyDisplay(*td);
		}
		else if(rand_num >= 14 && rand_num <= 15){
			symbol = 'M';
			elist[index] = new Enemy(row,col,symbol);

			elist[index]->notifyDisplay(*td);
		}
		else{
			symbol = 'X';
			elist[index] = new Enemy(row,col,symbol);

			elist[index]->notifyDisplay(*td);
		}
	}

	enemyindex++;
	
	myfile.close();
}

void GameBoard::setBoard(){
	setStair();
	
	for(int i=0;i<10; i++){	//	potion
		setItem(6,i);
	}
	for(int i=0; i<10; i++){	// gold
		setItem(8,i);	//	Merchant horded is not generated randomly
	}
	for(int i=0; i<20; i++){
		setEnemies(i);
	}
}


int GameBoard::getLevel(){
	return level;
}

double GameBoard::getScore(){
	if(p->getRace() == "Human"){
		score = 1.5 * p->getGold();
	}
	else if(p->getRace() == "Dwarf"){
		score = p->getGold() * 2;
	}
	else if(p->getRace() == "Orc"){
		score = p->getGold()/2;
	}
	else{
		score = p->getGold();
	}
	return score;
}

std::string GameBoard::getPlayerRace(){
	return p->getRace();
}

std::string GameBoard::getPlayerHP(){
	std::ostringstream os;
	os << p->getHP();
	return os.str();
}

std::string GameBoard::getPlayerGold(){
	int gold = p->getGold();

	std::ostringstream os;
	os << gold;

	return os.str();
}

std::string GameBoard::getPlayerAtk(){
	std::ostringstream os;
	os << p->getAtk();
	return os.str();
}

std::string GameBoard::getPlayerDef(){
	std::ostringstream os;
	os << p->getDef();
	return os.str();
}

std::string GameBoard::getActionMessage(){
	return ActionMessage;
}

std::string GameBoard::getStrLevel(){
	std::ostringstream os;
	if(level <=5){
		os << level;
	}
	else{
		os << (level-1);
	}
	
	return os.str();
}

bool GameBoard::getGameStart(){
	return gameStart;
}

Gold* GameBoard::getHorde(int row,int col){
	Gold *g;

	for(int i =0; i < goldindex; i++){
		if(glist[i]->getRow() == row){
			if(glist[i]->getCol() == col){
				g = glist[i];
				break;
			}
		}
	}

	return g;
}

Potion* GameBoard::getPotion(int row,int col){
	Potion *po;

	for(int i =0; i < 10; i++){
		if(plist[i]->getRow() == row){
			if(plist[i]->getCol() == col){
				po = plist[i];
				break;
			}
		}
	}

	return po;
}

Enemy* GameBoard::getEnemy(int row, int col){

	Enemy *em;

	for(int i =0; i < 20; i++){
		if(elist[i]->getRow() == row){
			if(elist[i]->getCol() == col){
				em = elist[i];
				break;
			}
		}
	}
	
	return em;
}

Dragon* GameBoard::getDragon(int row,int col){
	Dragon *dr;

	for(int i =0; i < dragonindex; i++){
		if(dlist[i]->getRow() == row){
			if(dlist[i]->getCol() == col){
				dr = dlist[i];
			}
		}
	}

	return dr;
}

void GameBoard::DragonHordeObserve(Gold *g){
	int row = g->getRow();
	int col = g->getCol();

	Dragon *d = getDragon(g->getDragonRow(),g->getDragonCol());

	if(td->getSymbol(row-1,col-1) == '@'){
		d->notifyHostility(true);
	}

	else if(td->getSymbol(row-1,col) == '@'){
		d->notifyHostility(true);
	}

	else if(td->getSymbol(row-1,col+1) == '@'){
		d->notifyHostility(true);
	}

	else if(td->getSymbol(row,col-1) == '@'){
		d->notifyHostility(true);
	}

	else if(td->getSymbol(row,col+1) == '@'){
		d->notifyHostility(true);
	}

	else if(td->getSymbol(row+1,col-1) == '@'){
		d->notifyHostility(true);
	}

	else if(td->getSymbol(row+1,col) == '@'){
		d->notifyHostility(true);
	}

	else if(td->getSymbol(row+1,col+1) == '@'){
		d->notifyHostility(true);
	}

	else{
		d->notifyHostility(false);
	}

}

std::ostream &operator<<(std::ostream &out, GameBoard &gb){
	out << *(gb.td) << std::endl;
	
	if(gb.getGameStart()){
		out << "Race: " << gb.getPlayerRace() << " Gold: " << gb.getPlayerGold() << "						Floor " << gb.getStrLevel() << "	" << std::endl;
		out << "HP: " << gb.getPlayerHP() << std::endl;
		out << "Atk: " << gb.getPlayerAtk() << std::endl;
		out << "Def: " << gb.getPlayerDef() << std::endl;
		out << "Action: " << gb.getActionMessage() << std::endl;
	}
	return out;
}
