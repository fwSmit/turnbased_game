#pragma once
#include "Game.h"
#include "Bot.h"

class tictactoe : public Game{
	friend  class Bot;
	Bot bot;
	State state;
	bool hasWon() override; // current player has won 
	std::vector<Move2D> getAvailableMoves() const ;
	const static size_t XSize = 3;
	const static size_t YSize = 3;
	constexpr unsigned int getXSize() const {return XSize;}
	constexpr unsigned int getYSize() const {return YSize;}
	int getBoardScore(unsigned int depth) override;
	Move2D getBotMove() ;// fetches the best move from the bot
	Move2D getUserMove() ; // asks the user which move they wanna play user input 
public:
	void startGame() override; // will loop if it's in command line mode, if not the function loop will need to be called for the game to continue
	bool hasEnded();
	bool isLegalMove(Move2D move) const;
	void playMove(Move2D move) ;
	tictactoe(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode);
};
