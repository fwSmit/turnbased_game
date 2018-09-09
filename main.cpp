#include <iostream>
#include <string>
#include <sstream>
#include "tictactoe.h"
#include "connect4.h"


using namespace std;

int main(){
	connect4 game;
	game.printBoard();
	while(!game.hasEnded()){
		game.nextPlayer();
        cout << "it's player " << game.getCurrentPlayerPiece().getValue() << "'s turn" << endl;
		game.takeUserInput();
		game.printBoard();
	}
}

