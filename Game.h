#pragma once
#include <vector>

enum pieceType : char {player1 = 'X', player2 = 'O', empty = ' '};

struct Piece{ 
	pieceType p = pieceType::empty;
	char getValue() const { return p; } 
	Piece(){}
	Piece(pieceType	val) : p(val) {}
};
struct Move{
	int x, y;
	Move() {x = 0; y = 0;};
	Move(int _x, int _y) : x(_x), y(_y) {};
};

struct Board{
	std::vector<std::vector<Piece>> board;
	Board(){}
	virtual char get(int x, int y) const{ 
		return board[x][y].getValue();
	}
	void setSize(int xSize, int ySize){
		std::vector<Piece> empty_line;
		empty_line.resize(ySize); // uses default constructor of piece, so empty piece
		board.resize(xSize, empty_line);
	}
	void set(int x, int y, Piece val){ 
		//std::cout << "setting " << x << ", " << y << " to " << val.getValue() << std::endl;
		board[x][y] = val;
	}

	bool isFull(){
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(get(i, j) == pieceType::empty) {
					return false;
				}
			}
		}
		return true;
	}
};
struct Score;

class Game{
protected:
	template <typename T>
		friend  class Bot;
	Board board;
	enum player_t : int {player_1, player_2};
	int player = player_t::player_1;
	bool isAITurn = false;
	virtual bool isBoardFull(){return board.isFull();}
	virtual std::vector<Move> getAvailableMoves() const = 0;
	virtual Score getBoardScore() = 0;
public:
	virtual void playMove(Move move) = 0;
	virtual void nextPlayer();
	virtual Piece getCurrentPlayerPiece();
	virtual void printBoard() = 0;
	virtual bool hasWon() = 0; // has the current player won?
	Game(bool isFirstPlayerAI, bool isSecondPlayerAI);
private:
};

