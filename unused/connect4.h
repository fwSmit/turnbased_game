#pragma once
#include "Game.h"
#include "Bot.h"

class connect4 : public Game{
	friend  class Bot;
	Bot bot;
	State state;
	const static size_t XSize = 7;
	const static size_t YSize = 6;
	constexpr int getXSize() const {return XSize;}
	constexpr int getYSize() const {return YSize;}
	Move getMove(int x) const;
	bool hasWon() override; // current player has won 
	bool isLegalMove(Move move) const;
	std::vector<Move> getAvailableMoves() const override;
	Score getBoardScore(unsigned int depth) override;
	Move getBotMove() override;
	Move getUserMove() override;
public:
	void startGame() override;
	void playMove(Move move) override;
	bool hasEnded();
	connect4(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode);
	void printBoard() override;
	//void takeUserInput();
};
