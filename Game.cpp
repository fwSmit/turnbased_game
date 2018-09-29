#include "Game.h"
#include <iostream>

Game::Game(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode) 
	: isFirstPlayerAI(_isFirstPlayerAI), isSecondPlayerAI(_isSecondPlayerAI), commandLineMode(_commandLineMode){
	
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

Piece Game::getCurrentPlayerPiece() const {
	Piece currPiece;
	if(player == player_t::player_1){
		currPiece = pieceType::player1;
	}else{
		currPiece = pieceType::player2;
	}
	return currPiece;
}

Piece Game::getOtherPlayerPiece() const {
	Piece currPiece;
	if(player == player_t::player_1){
		currPiece = pieceType::player2;
	}else{
		currPiece = pieceType::player1;
	}
	return currPiece;
}

bool Game::isAITurn(){
	if(player == player_t::player_1){
		return isFirstPlayerAI;
	}
	else {
		return isSecondPlayerAI;
	}
}

void Game::getMove(){
	if(isAITurn()){
		playMove(getBotMove());
	}
	else{
		playMove(getUserMove());
	}
}

void Game::printMove(Move move) const {
	std::cout << move.x + 1 << ", " << move.y + 1 << std::endl;
}
