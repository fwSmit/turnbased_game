#include <iostream>
#include "tictactoe.h"

using namespace std;

int main(){
	tictactoe game(true, false, true);
	game.test();
	game.startGame();
}
