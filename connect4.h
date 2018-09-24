#pragma once
#include "Game.h"

class connect4 : public Game{
	template <typename T>
		friend  class Bot;
	const static size_t XSize = 7;
	const static size_t YSize = 6;
	constexpr int getXSize() const {return XSize;}
	constexpr int getYSize() const {return YSize;}
	Move getMove(int x) const;
	bool hasWon() override; // current player has won 
	bool isLegalMove(Move move) const;
	std::vector<Move> getAvailableMoves() const override;
	Score getBoardScore() override;
public:
	void playMove(Move move) override;
	bool hasEnded();
	connect4();
	void printBoard() override;
	void takeUserInput();
};
