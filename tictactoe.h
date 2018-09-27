#pragma once
#include "Game.h"
#include "Bot.h"

class tictactoe : public Game{
	template <typename T>
		friend  class Bot;
	Bot <tictactoe> bot;
	const unsigned int botDepth = 5;
	bool hasWon() override; // current player has won 
	std::vector<Move> getAvailableMoves() const override;
	const static size_t XSize = 3;
	const static size_t YSize = 3;
	constexpr int getXSize() const {return XSize;}
	constexpr int getYSize() const {return YSize;}
	Score getBoardScore() override;
	Move getBotMove() override;// fetches the best move from the bot
	Move getUserMove() override; // asks the user which move they wanna play user input 
public:
	void startGame() override; // will loop if it's in command line mode, if not the function loop will need to be called for the game to continue
	Piece getCurrentPlayerPiece() override;
	bool hasEnded();
	bool isLegalMove(Move move) const;
	void playMove(Move move) override;
	tictactoe(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode);
	void printBoard() override;
};
