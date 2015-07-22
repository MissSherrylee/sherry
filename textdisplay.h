#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <string>
#include <fstream>

class TextDisplay{
	char **theDisplay;
	int gridRow,gridCol;
	std::string filename;

public:
	TextDisplay(std::string &name);
	~TextDisplay();
	
	void notify(int,int,char);
	char getSymbol(int,int);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif