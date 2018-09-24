#include <iostream>
#include <string>
#include <sstream>
#include "tictactoe.h"
#include "connect4.h"
#include "Bot.h"


using namespace std;

enum currentGame {g_connect4, g_tictactoe};


int main(){
	bool botBegins = false;
	currentGame cur = currentGame::g_connect4;
	if(cur == currentGame::g_connect4){
		connect4 game;
		Bot<connect4> bot;
		//game.nextPlayer();
		//game.playMove(Move(0, 0));
		//game.playMove(Move(1, 1));
		//game.playMove(Move(2, 2));
		bool botTurn = botBegins;
		game.printBoard();
		while(!game.hasEnded()){
			game.nextPlayer();
			if(botTurn){
				cout << "it's player " << game.getCurrentPlayerPiece().getValue() << "'s turn" << endl;
				cout << "(bot's turn)" << endl;
				Move move = bot.getBestMove(game, 3);
				cout << "Bot's move: " << move.x+1 << endl;
				game.playMove(move);
			}
			else{
				cout << "it's player " << game.getCurrentPlayerPiece().getValue() << "'s turn" << endl;
				game.takeUserInput();
			}
			game.printBoard();
			botTurn = !botTurn;
		}
	}
	if(cur == currentGame::g_tictactoe){
		tictactoe game;
		Bot<tictactoe> bot;
		bool botTurn = botBegins;
		game.printBoard();
		while(!game.hasEnded()){
			game.nextPlayer();
			if(botTurn){
				cout << "It's bot's turn" << endl;
				Move move = bot.getBestMove(game, 5);
				cout << "Bot's move: " << move.x+1 << ", " << move.y+1 << endl;
				game.playMove(move);
			}
			else{
				cout << "it's player " << game.getCurrentPlayerPiece().getValue() << "'s turn" << endl;
				game.takeUserInput();
			}
			game.printBoard();
			botTurn = !botTurn;
		}
		
	}
}

