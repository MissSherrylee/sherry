#include <iostream>
#include <string>
#include <fstream>

#include "GameBoard.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "gold.h"
#include "dragon.h"
#include "textdisplay.h"
using namespace std;

int main(){
	string command;
	ifstream ifs("start.txt");
	string line;

	while(!ifs.eof()){
		getline(ifs,line);
		cout << line << endl;
	}

	while(true){

		GameBoard *gb = new GameBoard();
		
		cout << *(gb);

		cout << "\033[1;31mPlease enter 'h','e','d','o' for selecting race and start the game: \033[0m\n" << endl;

		while(cin >> command && command != "q"){

			if(command == "h" || command == "e" || command == "d" || command == "o"){
				gb->SelectRace(command);
				gb->setBoard();
				cout << *(gb);
				break;
			}

			cout << "\033[1;31mPlease enter 'h','e','d','o' for selecting race and start the game: \033[0m\n" << endl;
		}


		while(cin >> command && !gb->isDead() && gb->getLevel() <= 5 &&  command != "q"){

			if(command == "no" || command == "so" || command == "ea" || command == "we" || command == "nw" || command == "ne" || command == "sw" || command == "se"){
				gb->MovePlayer(command);
				cout << *(gb);
			}

			if(command == "a"){
				cin >> command;
				gb->AttackEnemy(command);
				cout << *(gb);
			}

			if(command == "u"){
				cin >> command;
				gb->UseItem(command);
				cout << *(gb);
			}

			if(command == "r"){
				break;
			}

		}

		if(gb->getLevel() == 6){
			cout << endl;
			cout << "You Win!" << endl;
			cout << "SCORE : " << gb->getScore() << endl; 
			cout << endl;
			break;
		}

		if(gb->isDead()){
			cout << endl;
			cout << "The player is dead. Please try again !" << endl;
			cout << "SCORE : " << gb->getScore() << endl; 
			cout << endl;
		}

		if(command == "q")	{
			cout << endl;
			cout << "SCORE : " << gb->getScore() << endl; 
			cout << endl;
			
			break;
		}	

	}
}