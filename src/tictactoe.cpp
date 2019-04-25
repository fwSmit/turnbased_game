#include "tictactoe.h"
#include "Bot.h"
#include <string>
#include <sstream>
#include <cassert>

tictactoe::tictactoe(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode) : Game(_isFirstPlayerAI, _isSecondPlayerAI, _commandLineMode){
	state.board.setSize(XSize, YSize);
}

bool tictactoe::isLegalMove(Move2D move) const{
	if(move.x >= getXSize() || move.y >= getYSize()){ //check if move is in bounds
		return false;
	}
	if(state.board.get(move.x, move.y) != pieceType::empty){ // check if place is occupied
		return false;
	}
	return true;
}

bool tictactoe::hasEnded(){
	return isBoardFull() || hasWon();
}

void tictactoe::playMove(Move2D move){
	if(isLegalMove(move)){
		//std::cout << "Playing move " << move.x << ", " << move.y << std::endl;
		state.board.set(move.x, move.y, getCurrentPlayerPiece());
		//std::cout << "Has current player won? " << std::boolalpha << hasWon() << std::endl;
	}
	else{ // illegal move
		std::cout << "Move " << move.x << ", " << move.y << " is illegal" << std::endl;
	}
}

bool tictactoe::hasWon() {
    int count_cross_forward = 0; /*       "/"     (top right to left bottom)*/
    int count_cross_backward = 0; /*      "\"     (top left to right bottom)*/
    for(int i = 0; i < 3; i++) {
		int count_vertical = 0;
		int count_horizontal = 0;
        for(int j = 0; j < 3; j++) {
            if(state.board.get(i, j) == getCurrentPlayerPiece().getValue()) {
                count_vertical++;
            }
            if(state.board.get(j, i)  == getCurrentPlayerPiece().getValue()) {
                count_horizontal++;
            }
        }

        if(state.board.get(i, i) == getCurrentPlayerPiece().getValue()) {
            count_cross_backward++;
        }
        if(state.board.get(2 - i, i) == getCurrentPlayerPiece().getValue()) {
            count_cross_forward++;
        }

        if (count_vertical == 3 || count_horizontal == 3 ) { return true; }
    }
    if(count_cross_backward == 3 || count_cross_forward == 3) { return true; }
    return false;

}

std::vector<Move2D> tictactoe::getAvailableMoves() const{
	std::vector<Move2D> result;
	for(unsigned int x = 0; x < getXSize(); x++){
		for(unsigned int y = 0; y < getYSize(); y++){
			Move2D actualMove = Move2D(x, y);
			//std::cout << "checking move " << x << std::endl;
			if(isLegalMove(actualMove)){
				result.push_back(actualMove);
				//std::cout << "Possible move added" << std::endl;
			}
		}
	}
	return result;
}

int tictactoe::getBoardScore(unsigned int depth){
	return 0;
}

Move2D tictactoe::getBotMove(){
	return bot.getBestMove<decltype(*this), Move2D>(*this, botDepth);
}

Move2D tictactoe::getUserMove(){
	if(commandLineMode){
		std::cout << "type X_POSITION, Y_POSITION and press enter" << std::endl;
		int x, y;
		std::string input;

		while(1) {
			std::getline (std::cin, input);
			std::size_t found = input.find(",");
			if(found != std::string::npos) {
				input.replace(found, 1, " ");
			}
			std::cout << "input " << input << std::endl;
			std::stringstream ss(input);
			if(ss >> x >> y && isLegalMove(Move2D(x-1, y-1))) {
				break;
			}
			std::cout << "input not correct" << std::endl;
			std::cin.clear();
		}
		return Move2D(x-1, y-1);
	}
	else{
		std::cout << "This game only works in command line mode" << std::endl;
		assert(0);
		return Move2D(0, 0);
	}
}

void tictactoe::startGame(){
	if(commandLineMode){
		state.board.print();
		while(!hasEnded()){
			nextPlayer();
			Move2D move;
			if(isAITurn()){
				std::cout << "it's player " << getCurrentPlayerPiece().getValue() << "'s turn" << std::endl;
				std::cout << "(bot's turn)" << std::endl;
				move = getBotMove();
				std::cout << "Bot's move: ";
				move.print();
			}
			else{
				std::cout << "it's player " << getCurrentPlayerPiece().getValue() << "'s turn" << std::endl;
				move = getUserMove();
			}
			playMove(move);
			std::cout << "Possible move size " << getAvailableMoves().size() << std::endl;
			state.board.print();
			if(hasWon()){
				std::cout << "Game has ended, player " << getCurrentPlayerPiece().getValue() << " has won" << std::endl;
			}
			else{
				std::cout << "This game has ended in a tie" << std::endl;
			}
		}
	}
	else{
		std::cout << "This game only works in command line mode" << std::endl;
		assert(0);
	}
}
