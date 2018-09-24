#pragma once
#include "Game.h"

class tictactoe : public Game{
	template <typename T>
		friend  class Bot;
	bool hasWon() override; // current player has won 
	std::vector<Move> getAvailableMoves() const override;
	const static size_t XSize = 3;
	const static size_t YSize = 3;
	constexpr int getXSize() const {return XSize;}
	constexpr int getYSize() const {return YSize;}
	Score getBoardScore() override;
public:
	void takeUserInput();
	Piece getCurrentPlayerPiece() override;
	bool hasEnded();
	bool isLegalMove(Move move) const;
	void playMove(Move move) override;
	tictactoe(bool isFirstPlayerAI, bool isSecondPlayerAI);
	void printBoard() override;
};
