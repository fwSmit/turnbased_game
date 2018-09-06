#include <vector>
#include <iostream>

enum pieceType : char {player1 = 'X', player2 = 'O', empty = ' '};

struct Piece{ 
	pieceType p = pieceType::empty;
	char getValue(){ return p; } 
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
	virtual char get(int x, int y){ 
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
class Game{
protected:
	Board board;
public:
	virtual void makeMove(Move move){};
	virtual void printBoard(){};
	virtual std::vector<Move> getAvailableMoves(){ return std::vector<Move>();};
	virtual bool hasWon(){ return bool();}; // has the current player won?
	Game();
private:
	virtual void nextPlayer(){};
};

