#include "Reversi.h"
#include "Bot.h"
#include <sstream>

Reversi::Reversi(bool _isFirstPlayerAI, bool _isSecondPlayerAI, bool _commandLineMode) : Game(_isFirstPlayerAI, _isSecondPlayerAI, _commandLineMode){
	board.setSize(getXSize(), getYSize());
	board.set(3, 4, pieceType::player1);
	board.set(4, 3, pieceType::player1);
	board.set(3, 3, pieceType::player2);
	board.set(4, 4, pieceType::player2);
	//playMove(Move(3, 3));
	//playMove(Move(4, 4));
	//nextPlayer();
	//playMove(Move(3, 4));
	//playMove(Move(4, 3));
	//nextPlayer();
}

bool Reversi::isInBounds(Move move) const{
	bool inBounds = move.x >= 0 && move.y >= 0 && move.x < getXSize() && move.y < getYSize();
	return inBounds;
}

bool Reversi::hasWon(){
	int score1 = getPlayerScore(pieceType::player1);
	int score2 = getPlayerScore(pieceType::player2);
	if(getCurrentPlayerPiece().getValue() == pieceType::player1){
		return hasEnded() && score1 > score2;
	}
	else{
		return hasEnded() && score2 > score1;
	}
}

bool Reversi::isLegalMove(Move move) const {
	if(!isInBounds(move)){
			return false;
	}
	if(board.get(move.x, move.y) != pieceType::empty){ // check if place is occupied
		return false;
	}
	for(int x_direction = -1; x_direction <= 1; x_direction++){ // checks if there is an adjacent piece from oppossing player
		for(int y_direction = -1; y_direction <= 1; y_direction++){
			if(!(x_direction == 0 && y_direction == 0)){
				Move testMove(move.x + x_direction, move.y + y_direction);
				//printMove(testMove);
				if(isInBounds(testMove)){
					if(board.get(testMove.x, testMove.y) == getOtherPlayerPiece().getValue()) {
						do{
							if(board.get(testMove.x, testMove.y) == getCurrentPlayerPiece().getValue()){
								//std::cout << "found own piece at ";
								//printMove(testMove);
								return true;
							}
							testMove = Move(testMove.x + x_direction, testMove.y + y_direction);
						}while(isInBounds(testMove) && board.get(testMove.x, testMove.y) != pieceType::empty);
					}
				}
			}
		}
	}
	//std::cout << "No piece on the other side" << std::endl;
	return false;
}

bool Reversi::hasEnded(){
	if( isBoardFull() || !canAPlayerMove())
	{
		std::cout << "Game has ended because";
		if(isBoardFull()){
			std::cout << " the board is full" << std::endl;
		}
		else{
			std::cout << " neither player could make a move" << std::endl;
		}
		return true;
	}
	else{
		return false;
	}
}

bool Reversi::canAPlayerMove(){
	bool canFirstPlayerMove = (getAvailableMoves().size() != 0);
	nextPlayer();
	bool canSecondPlayerMove = (getAvailableMoves().size() != 0);
	nextPlayer();
	return canFirstPlayerMove || canSecondPlayerMove;
}

void Reversi::printBoard(){
	// hacky way of making sure it's the right player's turn
	nextPlayer(); // don't forget the one at the end of this function
    std::string spacing = "     ";
    std::string horizontalLine = "    --  --  --  --  --  --  -- --";
	std::cout << spacing << horizontalLine << std::endl;
	for(int y = 0; y < getYSize(); y++) {
		std::cout << spacing << y+1 << " " << "| ";
		for(int x = 0; x < getXSize(); x++) {
			if(board.get(x, y) == pieceType::empty){
				char c;
				if(isLegalMove(Move(x, y))){
						c = '*';
				}else{
					c = ' ';
				}	
				std::cout << c << " | ";
			}
			else{
				std::cout << board.get(x, y) << " | ";
			}
		}
		std::cout << std::endl << spacing << horizontalLine << std::endl;
	}
	std::cout << spacing << "    ";
	for (int x = 0; x < getXSize(); x++) {
		std::cout<< x+1 << "   ";
	}
	std::cout << std::endl;
	nextPlayer(); // Don't forget this one
}

std::vector<Move> Reversi::getAvailableMoves() const{
	std::vector<Move> result;
	for(int x = 0; x < getXSize(); x++){
		for(int y = 0; y < getYSize(); y++){
			Move actualMove = Move(x, y);
			//std::cout << "checking move " << x << std::endl;
			if(isLegalMove(actualMove)){
				result.push_back(actualMove);
				//std::cout << "Possible move added" << std::endl;
			}
		}
	}
	return result;
}

void Reversi::playMove(Move move){
	if(isLegalMove(move)){
		board.set(move.x, move.y, getCurrentPlayerPiece());

		for(int x_direction = -1; x_direction <= 1; x_direction++){ // flips pieces in between
			for(int y_direction = -1; y_direction <= 1; y_direction++){
				if(!(x_direction == 0 && y_direction == 0)){
					Move testMove(move.x + x_direction, move.y + y_direction);
					//printMove(testMove);
					if(isInBounds(testMove)){
						if(board.get(testMove.x, testMove.y) == getOtherPlayerPiece().getValue()) {
							std::vector<Move> enemyPieces;
							bool isEnemyPiece;
							do{
								enemyPieces.push_back(testMove);
								testMove = Move(testMove.x + x_direction, testMove.y + y_direction);
							}while(isInBounds(testMove) && board.get(testMove.x, testMove.y) == getOtherPlayerPiece().getValue());
							if(isInBounds(testMove) && board.get(testMove.x, testMove.y) == getCurrentPlayerPiece().getValue()){
								for(Move m : enemyPieces){
									flipPiece(m);
								}
							}
							//enemyPieces.clear(); // is not needed as it goes out of scope
						}
					}
				}
			}
		}
	}
	else{ // illegal move
		std::cout << "Move " << move.x << ", " << move.y << " is illegal" << std::endl;
	}
}

void Reversi::flipPiece(Move position){
	char piece = board.get(position.x, position.y);
	bool isEmpty = (piece == pieceType::empty);
	assert(!isEmpty);
	if(piece == pieceType::player1){
		board.set(position.x, position.y, pieceType::player2);
	}
	else{ // piece == pieceType::player2
		board.set(position.x, position.y, pieceType::player1);
	}
}

int Reversi::getPlayerScore(Piece playerPiece) const {
	int score = 0;
	for(int x = 0; x < getXSize(); x++){
		for(int y = 0; y < getYSize(); y++){
			if(board.get(x, y) == playerPiece.getValue()){
				score++;
			}
		}
	}
	return score;
}

Score Reversi::getBoardScore(unsigned int depth){ // EDIT
	auto availableMoves = getAvailableMoves();
	int score = 0;
	for(Move m: availableMoves){
		m.y -= 1;
		if(isLegalMove(m)){
			//std::cout << "move is valid" <<  std::endl;
			Reversi temp = *this;
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

Move Reversi::getBotMove(){
	return bot.getBestMove(*this, botDepth);
}

Move Reversi::getUserMove(){
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
			//std::cout << "input " << input << std::endl;
			std::stringstream ss(input);
			if(ss >> x >> y && isLegalMove(Move(x-1, y-1))) {
				break;
			}
			std::cout << "input not correct" << std::endl;
			std::cin.clear();
		}
		return Move(x-1, y-1);
	}
	else{
		std::cout << "This game only works in command line mode" << std::endl;
		assert(0);
		return Move(0, 0);
	}
}

void Reversi::startGame(){
	if(commandLineMode){
		//for(int x = 0; x < getXSize()+3; x ++){
			//for(int y = 0; y < getYSize()+3; y++){
				//Move move(x, y);
				//printMove(move);
				////std::cout << "In bounds: " << std::boolalpha << isInBounds(move) << std::endl;
				//std::cout << "Is legal: " << std::boolalpha << isLegalMove(move) << std::endl;
			//}
		//}
		printBoard();
		while(!hasEnded()){
			nextPlayer();
			//std::cout << "Number of possible moves: " << getAvailableMoves().size() << std::endl;
			Move move;
			//for(Move m : getAvailableMoves()){
				//printMove(m);
			//}
			if(getAvailableMoves().size() == 0){
				// skip move
				std::cout << "No moves available. Passing" << std::endl;
			}
			else{
				if(isAITurn()){
					std::cout << "it's player " << getCurrentPlayerPiece().getValue() << "'s turn" << std::endl;
					std::cout << "(bot's turn)" << std::endl;
					move = getBotMove();
					std::cout << "Bot's move: " << move.x+1 << std::endl;
				}
				else{
					std::cout << "it's player " << getCurrentPlayerPiece().getValue() << "'s turn" << std::endl;
					move = getUserMove();
				}
				playMove(move);
				std::cout << "Current score: (" << char(pieceType::player1) << ") " << getPlayerScore(pieceType::player1) << " - (" << char(pieceType::player2) << ") " << getPlayerScore(pieceType::player2) << std::endl;
				printBoard();
			}
		}

		int score1 = getPlayerScore(pieceType::player1);
		int score2 = getPlayerScore(pieceType::player2);

		if(score1 == score2){
			std::cout << "Game has ended in a tie" << std::endl;
		}
		else{
			char playerPiece;
			if(score1 > score2){
				playerPiece = pieceType::player1;
			}
			else{
				playerPiece = pieceType::player2;
			}
			std::cout << "Game has ended, player " << playerPiece << " has won" << std::endl;
		}
	}
	else{
		std::cout << "This game only works in command line mode" << std::endl;
		assert(0);
	}
}
