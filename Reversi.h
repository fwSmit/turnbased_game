#pragma once
#include "Game.h"
#include "Bot.h"

class Reversi : public Game{
	template <typename T>
		friend  class Bot;
	Bot <Reversi> bot;
	const unsigned int botDepth = 3;
	const static size_t XSize = 8;
	const static size_t YSize = 8;
	constexpr int getXSize() const {return XSize;}
	constexpr int getYSize() const {return YSize;}
	bool isLegalMove(Move move) const;
	bool isInBounds(Move move) const;
	std::vector<Move> getAvailableMoves() const override;
	Score getBoardScore(unsigned int depth) override;
	Move getBotMove() override;
	Move getUserMove() override;
	void flipPiece(Move position);
	bool canAPlayerMove(); // returns true if either player is able to move
	int getPlayerScore(Piece playerPiece) const;
	bool hasWon() override;
public:
	void startGame() override;
	void playMove(Move move) override;
	bool hasEnded();
	Reversi(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode);
	void printBoard() override;
	//void takeUserInput();
};
