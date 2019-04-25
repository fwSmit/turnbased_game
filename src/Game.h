#pragma once
#include <vector>
#include <iostream>

enum pieceType : char {player1 = 'X', player2 = 'O', empty = ' '};

class Piece{ 
private:
	pieceType p = pieceType::empty;
public:
	char getValue() const { return p; } 
	Piece(){}
	Piece(pieceType	val) : p(val) {}
};
struct Move1D{
	unsigned int x;
	Move1D() {x = 0;};
	Move1D(unsigned int _x) : x(_x) {};
	void print(){
		std::cout << "move(" << x << ")" << std::endl;
	}
};

struct Move2D{
	unsigned int x, y;
	Move2D() {x = 0; y = 0;};
	Move2D(unsigned int _x, unsigned int _y) : x(_x), y(_y) {};
	void print(){
		std::cout << "move(" << x << ", " << y  << ")" << std::endl;
	}
};

struct Board{
	std::vector<std::vector<Piece>> board;
	unsigned int xSize, ySize;
	Board(){}
	virtual char get(unsigned int x, unsigned int y) const{ 
		if(x >= xSize || y >= ySize){
			std::cout << "out of bounds" << std::endl;
			std::cout << "the move was: " << x << ", " << y << std::endl;
			
		}
		return board[x][y].getValue();
	}
	void setSize(int _xSize, int _ySize){
		xSize = _xSize;
		ySize = _ySize;
		std::vector<Piece> empty_line;
		empty_line.resize(ySize); // uses default constructor of piece, so empty piece
		board.resize(xSize, empty_line);
	}
	void set(int x, int y, Piece val){ 
		//std::cout << "setting " << x << ", " << y << " to " << val.getValue() << std::endl;
		board[x][y] = val;
	}

	bool isFull(){
		for(unsigned int i = 0; i < xSize; i++) {
			for(unsigned int j = 0; j < ySize; j++) {
				if(get(i, j) == pieceType::empty) {
					return false;
				}
			}
		}
		return true;
	}

	void print(){
		std::string spacing = "     ";
		std::string horizontalLine;
		for(unsigned int x = 0; x < xSize; x++){
			 horizontalLine += "  --";
		}
		std::cout << spacing << horizontalLine << std::endl;
		for(unsigned int y = 0; y < ySize; y++) {
			std::cout << spacing << "| ";
			for(unsigned int x = 0; x < xSize; x++) {
				std::cout << get(x, y) << " | ";
			}
			std::cout << std::endl << spacing << horizontalLine << std::endl;
		}
	}
};

struct State{
	Board board;
	enum player_t : int {player_1, player_2};
	int player = player_t::player_2;  // player one will still start because nextPlayer() will be called at the beginning of a game loop (see connect4::startGame())
};

class Game{
	// two player turn based game
protected:
	friend  class Bot;
	State state;
	const unsigned int botDepth = 5;
	bool isFirstPlayerAI;
	bool isSecondPlayerAI;
	bool commandLineMode;
	virtual bool isBoardFull(){return state.board.isFull();}
	virtual int getBoardScore(unsigned int depth) = 0;
	bool isAITurn();
	void getMove(); // either takes input from the user or makes the bot decide for the best move
					// depending on whose turn it is
public:
	/* maybe this function could be implemented in Game */
	virtual void startGame() = 0; // will loop if it's in command line mode, if not the draw loop will need to be called for the game to continue
	virtual void nextPlayer();
	virtual Piece getCurrentPlayerPiece() const;
	virtual Piece getOtherPlayerPiece() const;
	virtual bool hasWon() = 0; // has the current player won?
	Game(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode = true);
private:
};

