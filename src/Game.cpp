#include <iostream>
#include "Game.h"

Game::Game(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode) 
	: isFirstPlayerAI(_isFirstPlayerAI), isSecondPlayerAI(_isSecondPlayerAI), commandLineMode(_commandLineMode){
	
}

void Game::nextPlayer(){
	if(state.player == State::player_t::player_1){
		state.player = State::player_t::player_2;
	}
	else{
		state.player = State::player_t::player_1;
	}
}

Piece Game::getCurrentPlayerPiece() const {
	Piece currPiece;
	if(state.player == State::player_t::player_1){
		currPiece = pieceType::player1;
	}else{
		currPiece = pieceType::player2;
	}
	return currPiece;
}

Piece Game::getOtherPlayerPiece() const {
	Piece currPiece;
	if(state.player == State::player_t::player_1){
		currPiece = pieceType::player2;
	}else{
		currPiece = pieceType::player1;
	}
	return currPiece;
}

bool Game::isAITurn(){
	if(state.player == State::player_t::player_1){
		return isFirstPlayerAI;
	}
	else {
		return isSecondPlayerAI;
	}
}

