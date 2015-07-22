// x: row; y : column
// room 1: x~[3, 6],  y~[3,30]
// room 2: else
// room 3: x~[10,12], y~[38, 49]
// room 4: x~[15, 21], y~[4, 24]
// room 5: x~[16, 21], y~[37, 75]
#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "gold.h"
#include "dragon.h"
#include "textdisplay.h"
#define b_row 25
#define b_column 79

class GameBoard{

	std::string filename;
	Enemy *elist[20];
	Potion *plist[10];
	Gold *glist[30];
	Dragon *dlist[30];	//	attack enemy CHANGE
	std::string revealist[6];	//	store potions not revealed
	
	TextDisplay *td;
	Player *p;	//	the player
	
	int room; // room that player stay
	int px, py;//current player position
	int level;
	int enemyindex;
	int goldindex;
	int dragonindex;
	int potionindex;
	double score;
	
	char prev;//the previous symbol of the current floor tile
	
	bool gameStart;
	
	std::string ActionMessage;
	
	//void AddNeighbour(int,int);
	void clearStat();
	void toNewLevel();
	void MoveEnemy();
	void setStair();
	void setItem(int,int);
	void setEnemies(int);
	void WatchMessage(int,int);
	void DragonHordeObserve(Gold *);
	void notifyTakePotion(Potion *);


	Gold* getHorde(int,int);
	Potion* getPotion(int,int);
	Enemy* getEnemy(int,int);
	Dragon* getDragon(int,int);



	public:
		GameBoard();
		~GameBoard();
		void MovePlayer(std::string &s);
		void UseItem(std::string &s);
		void AttackEnemy(std::string &s);
		bool isDead();
		void SelectRace(std::string &r);
		void setBoard();
		int getLevel();
		double getScore();
		bool getGameStart();
		std::string getPlayerRace();
		std::string getPlayerHP();
		std::string getPlayerGold();
		std::string getPlayerAtk();
		std::string getPlayerDef();
		std::string getActionMessage();
		std::string getStrLevel();
		friend std::ostream &operator<<(std::ostream&, GameBoard &);

};

#endif