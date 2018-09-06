#include <iostream>
#include <string>
#include <sstream>
#include "tictactoe.h"


using namespace std;

int main(){
	tictactoe game;
	//game.playMove(Move(0, 2));
	//game.playMove(Move(1, 2));
	//game.playMove(Move(1, 1));
	//game.playMove(Move(2, 2));
	//game.playMove(Move(2, 0));
	while(1){
		game.printBoard();
		cout << "type X_POSITION, Y_POSITION and press enter" << endl;
		cout << "for example \"1, 3\" ENTER" << endl;
		int x, y;
		string input;

		while(1) {
			std::getline (std::cin, input);
			std::size_t found = input.find(",");
			if(found != string::npos) {
				input.replace(found, 1, " ");
			}
			//cout << "input " << input << endl;
			stringstream ss(input);
			if(ss >> x >> y && game.isLegalMove(Move(x-1, y-1))) {
				break;
			}
			cout << "input not correct" << endl;
			cin.clear();
		}
		game.playMove(Move(x-1, y-1));
	}
}

