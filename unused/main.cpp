#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
////#include <SFML/Main.hpp>
//#include <SFML/Config.hpp>
#include "tictactoe.h"
#include "connect4.h"
#include "Reversi.h"
#include "Bot.h"


using namespace std;

enum currentGame {g_connect4, g_tictactoe, g_reversi};


int main(){

	//sf::ContextSettings settings;
	//sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
    //window.setMouseCursorVisible(0);
    //window.setVerticalSyncEnabled(1);
    ////window.setFramerateLimit(10);
    //while (window.isOpen()) {
        //window.display();
        ////std::cout << timer.restart().asMilliseconds() << std::endl;
    //}

	currentGame cur = currentGame::g_tictactoe;
	//currentGame cur = currentGame::g_reversi;
	//currentGame cur = currentGame::g_connect4;
	if(cur == currentGame::g_connect4){
		connect4 game(true, false, true);
		game.startGame();
	}
	if(cur == currentGame::g_tictactoe){
		// AI begins
		tictactoe game(true, false, true);
		// player begins
		//tictactoe game(false, true, true);
		//game.playMove(Move(2, 2));
		//game.nextPlayer();
		//game.playMove(Move(1, 1));
		////game.playMove(Move(1, 2));
		//game.nextPlayer();
		//game.playMove(Move(1-1, 1));
		//game.playMove(Move(1,0));
		//game.playMove(Move(1-1, 2));
		//game.playMove(Move(0, 0));
		//tictactoe game(true, false, true);
		// player begins
		// game.playMove(Move(1, 1));
		// game.playMove(Move(0, 1));
		// game.playMove(Move(2, 2));
		// game.nextPlayer();
		// game.playMove(Move(0, 0));
		// game.playMove(Move(0, 2));
		// game.playMove(Move(1, 2));
		// game.nextPlayer();
		game.startGame();
		//game.testGame();
	}
	if(cur == currentGame::g_reversi){
		Reversi game(false, false, true);
		game.startGame();
	}
}

