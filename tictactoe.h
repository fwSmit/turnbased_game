#include "Game.h"

class tictactoe : Game{
	bool hasWon() override; // current player has won 
	Piece getCurrentPlayerPiece();
public:
	bool isLegalMove(Move move);
	void playMove(Move move);
	tictactoe();
	void printBoard() override;
};
