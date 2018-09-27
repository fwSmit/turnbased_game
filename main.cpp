#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
////#include <SFML/Main.hpp>
//#include <SFML/Config.hpp>
#include "tictactoe.h"
#include "connect4.h"
#include "Bot.h"


using namespace std;

enum currentGame {g_connect4, g_tictactoe};


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
	if(cur == currentGame::g_connect4){
		connect4 game(true, false, true);
		game.startGame();
	}
	if(cur == currentGame::g_tictactoe){
		tictactoe game(true, false, true);
		game.startGame();
	}
}

