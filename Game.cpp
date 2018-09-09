#include "Game.h"

Game::Game(){
	
}

void Game::nextPlayer(){
	if(player == player_t::player_1){
		player = player_t::player_2;
	}else{
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
