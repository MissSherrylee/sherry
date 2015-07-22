#include "textdisplay.h"

TextDisplay::TextDisplay(std::string &name){
	filename = name;
	std::ifstream input(filename.c_str());
	std::string line;

	gridRow = 25;
	gridCol = 79;

	theDisplay = new char*[gridRow];

	if(input.is_open()){
		for(int i = 0; i < gridRow; i++){

			getline(input,line);

			theDisplay[i] = new char[gridCol];

			for(int j = 0; j < gridCol; j++){

				theDisplay[i][j] = line[j];
			}
		}
		input.close();
	}
}

TextDisplay::~TextDisplay(){
	for(int i = 0; i < gridRow; i++){
		delete [] theDisplay[i];
	}
	delete theDisplay;
}

void TextDisplay::notify(int row, int col, char symbol){
	theDisplay[row][col] = symbol;
}

char TextDisplay::getSymbol(int row,int col){
	return theDisplay[row][col];
}

std::ostream& operator<<(std::ostream &out, const TextDisplay &td){
	for(int i = 0; i < td.gridRow; i++){
		for(int j = 0; j < td.gridCol; j++){
			out << td.theDisplay[i][j];
		}
		out << std::endl;
	}

	return out;
}