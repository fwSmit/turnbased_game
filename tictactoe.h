#include "Game.h"

class tictactoe : Game{
	enum player_t : int {player_1, player_2};
	int player = player_t::player_1;
	void nextPlayer() override;
	bool hasWon() override; // current player has won 
	Piece getCurrentPlayerPiece();
public:
	bool isLegalMove(Move move);
	void playMove(Move move);
	tictactoe();
	void printBoard() override;
};
