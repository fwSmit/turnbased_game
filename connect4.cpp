#include "connect4.h"
#include "Bot.h"
#include <sstream>

connect4::connect4(bool isFirstPlayerAI, bool isSecondPlayerAI) : Game(isFirstPlayerAI, isSecondPlayerAI){
	board.setSize(getXSize(), getYSize());
	//playMove(getMove(0));
	//playMove(getMove(1));
	//playMove(getMove(2));
}

bool connect4::isLegalMove(Move move) const {
	if(move.x < 0 || move.y < 0 || move.x > getXSize() || move.y > getYSize()){ //check if move is in bounds
		return false;
	}
	if(board.get(move.x, move.y) != pieceType::empty){ // check if place is occupied
		return false;
	}
	return true;
}

bool connect4::hasEnded(){
	return isBoardFull() || hasWon();
}

void connect4::printBoard(){
    std::string spacing = "     ";
    std::string horizontalLine = "  --  --  --  --  --  --  --";
	std::cout << spacing << horizontalLine << std::endl;
	for(int y = 0; y < getYSize(); y++) {
		std::cout << spacing << "| ";
		for(int x = 0; x < getXSize(); x++) {
			std::cout << board.get(x, y) << " | ";
		}
		std::cout << std::endl << spacing << horizontalLine << std::endl;
	}
	std::cout << spacing << "  ";
	for (int y = 0; y <= getYSize(); y++) {
		std::cout<< y+1 << "   ";
	}
	std::cout << std::endl;
}

void connect4::takeUserInput(){
	std::cout << "type X_POSITION and press enter" << std::endl;
		int x;
		std::string input;

		while(1) {
			std::getline (std::cin, input);
			std::size_t found = input.find(",");
			if(found != std::string::npos) {
				input.replace(found, 1, " ");
			}
			//std::cout << "input " << input << std::endl;
			std::stringstream ss(input);
			if(ss >> x && isLegalMove(getMove(x-1))) {
				break;
			}
			std::cout << "input not correct" << std::endl;
			std::cin.clear();
		}
		playMove(getMove(x-1));
}

std::vector<Move> connect4::getAvailableMoves() const{
	std::vector<Move> result;
	//result.push_back(getMove(3));
	//return result;
	for(int x = 0; x < getXSize(); x++){
		Move actualMove = getMove(x);
		//std::cout << "checking move " << x << std::endl;
		if(isLegalMove(actualMove)){
			result.push_back(actualMove);
			//std::cout << "Possible move added" << std::endl;
		}
	}
	return result;
}

Move connect4::getMove(int x) const{ // this is done twice per move, but could be done only once per move
	int y = getYSize() - 1;
	for(; y >= 0; y--){
		if(board.get(x, y) == pieceType::empty) break;
	}
	return Move(x, y);
}

void connect4::playMove(Move move){
	if(isLegalMove(move)){
		//std::cout << "Playing move " << move.x << ", " << move.y << std::endl;
		board.set(move.x, move.y, getCurrentPlayerPiece());
		//std::cout << "Has current player won? " << std::boolalpha << hasWon() << std::endl;
	}
	else{ // illegal move
		std::cout << "Move " << move.x << ", " << move.y << " is illegal" << std::endl;
	}
}

bool connect4::hasWon() 
{
	bool won = false;
	char currPlayerPiece = getCurrentPlayerPiece().getValue();
	//winningPositions.clear();
	// horizontal win
	for(size_t yPos = 0; yPos < getYSize(); yPos ++) {
		for(size_t beginPos = 0; beginPos < getXSize() - 3; beginPos++) {
			unsigned int count = 0;
			for(size_t currPos = beginPos; currPos < beginPos +  4; currPos++) {
				if(board.get(currPos, yPos) == currPlayerPiece) {
					count++;
					//std::cout << "found horizontal piece at " << currPos << "	" << yPos << endl;
				}
			}
			//std::cout << "got " << count << endl;
			if (count == 4){
				//std::cout << "horizontal" << endl;
				//winningPositions.push_back(std::make_pair(sf::Vector2i(beginPos, yPos), sf::Vector2i(beginPos + 3, yPos)));
				won = true;
				//return true;
			}
		}
	}

	//vertical win
	for(size_t xPos = 0; xPos < getXSize(); xPos++){
		for(size_t yBegin = 0; yBegin < getYSize()-3; yBegin++){
			unsigned int count = 0;
			for(size_t curr = 0; curr < 4; curr++){
				if(board.get(xPos, yBegin+curr) == currPlayerPiece){
					count++;
					//std::cout << "found vertical piece at " << xPos << "	" << yBegin+curr << endl;
				}
			}
			if(count == 4){
				//std::cout << "vertical" << endl;
				//winningPositions.push_back(std::make_pair(sf::Vector2i(xPos, yBegin), sf::Vector2i(xPos, yBegin + 3)));
				won = true;
				//return true;
			}
		}
	}

	// across like \ (backslash) 
	for(size_t xPos = 0; xPos < getXSize()-3; xPos++){
		for(size_t yPos = 0; yPos < getYSize()-3; yPos++){
			unsigned int count = 0;
			for(size_t curr = 0; curr < 4; curr++){
				if(board.get(xPos+curr, yPos+curr) == currPlayerPiece){
					count++;
					//std::cout << "found piece at " << xPos+3-curr << "	" << yPos+curr << endl;
				}
			}
			if(count == 4){
				//std::cout << "backslash" << endl;
				//std::cout << xPos << "	" << yPos << endl;
				//winningPositions.push_back(std::make_pair(sf::Vector2i(xPos, yPos), sf::Vector2i(xPos + 3, yPos + 3)));
				won = true;
				//return true;
			}
		}
		//std::cout << "reset count " << endl;
	}


	// across like / (forward slash) 
	for(size_t xPos = 0; xPos < getXSize()-3; xPos++){
		for(size_t yPos = 0; yPos < getYSize()-3; yPos++){
			unsigned int count = 0;
			for(size_t curr = 0; curr < 4; curr++){
				if(board.get(xPos+curr, yPos+3-curr) == currPlayerPiece){
					count++;
				}
			}
			if(count == 4){
				//std::cout << "/" << endl;
				//winningPositions.push_back(std::make_pair(sf::Vector2i(xPos, yPos+3), sf::Vector2i(xPos + 3, yPos)));
				won = true;
				//return true;
			}
		}
	}
	return won;
}

Score connect4::getBoardScore(){ 
	auto availableMoves = getAvailableMoves();
	int score = 0;
	for(Move m: availableMoves){
		m.y -= 1;
		if(isLegalMove(m)){
			//std::cout << "move is valid" <<  std::endl;
			connect4 temp = *this;
			temp.playMove(m);
			if(temp.hasWon()){
				score += 100;	
			}
			temp.nextPlayer();
			if(temp.hasWon()){
				score -= 100;	
			}
		}

	}
	//std::cout << "score is " << score << std::endl;
	return Score(Result::t_score, score);
}
