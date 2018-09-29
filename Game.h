#pragma once
#include <vector>
#include <iostream>

enum pieceType : char {player1 = 'X', player2 = 'O', empty = ' '};

struct Piece{ 
	pieceType p = pieceType::empty;
	char getValue() const { return p; } 
	Piece(){}
	Piece(pieceType	val) : p(val) {}
};
struct Move{
	unsigned int x, y;
	Move() {x = 0; y = 0;};
	Move(unsigned int _x, unsigned int _y) : x(_x), y(_y) {};
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
		for(int i = 0; i < xSize; i++) {
			for(int j = 0; j < ySize; j++) {
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
	int player = player_t::player_2;  // player one will still start because nextPlayer() will be called at the beginning of a game loop (see connect4::startGame())
	bool isFirstPlayerAI;
	bool isSecondPlayerAI;
	bool commandLineMode;
	virtual bool isBoardFull(){return board.isFull();}
	virtual std::vector<Move> getAvailableMoves() const = 0;
	virtual Score getBoardScore() = 0;
	bool isAITurn();
	void getMove(); // either takes input from the user or makes the bot decide for the best move
					// depending on whose turn it is
	virtual Move getBotMove() = 0; // fetches the best move from the bot
	virtual Move getUserMove() = 0;	// asks the user which move they wanna play user input 
	void printMove(Move move) const;
public:
	/* maybe this function could be implemented in Game */
	virtual void startGame() = 0; // will loop if it's in command line mode, if not the function loop will need to be called for the game to continue
	
	virtual void playMove(Move move) = 0;
	virtual void nextPlayer();
	virtual Piece getCurrentPlayerPiece() const;
	virtual Piece getOtherPlayerPiece() const;
	virtual void printBoard() = 0;
	virtual bool hasWon() = 0; // has the current player won?
	Game(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode = true);
private:
};

