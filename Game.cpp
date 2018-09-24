#include "Game.h"
#include <iostream>

Game::Game(bool isFirstPlayerAI, bool isSecondPlayerAI){
	
}

void Game::nextPlayer(){
	//std::cout << "next player" << std::endl;
	if(player == player_t::player_1){
		player = player_t::player_2;
	}
	else{
		player = player_t::player_1;
	}
}

Piece Game::getCurrentPlayerPiece(){
	Piece currPiece;
	if(player == player_t::player_1){
		currPiece = pieceType::player1;
	}else{
		currPiece = pieceType::player2;
	}
	return currPiece;
}
