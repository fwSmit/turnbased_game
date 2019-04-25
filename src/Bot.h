#pragma once
#include "Game.h"
#include <iostream>
#include <vector>

class Bot{
	int number_evaluations = 0;
	// depth starts at 0 and ends when it's equal to maxDepth (0 <= depth <= maxDepth)
	// maxDepth is the maximum number of nodes the algorithm may travel down. If maxDepth is zero the algoritm will immediately return a value
	template <class T, class M>
	int getScore(T game, M move, int alpha, int beta, unsigned int depth, const unsigned int maxDepth){
		return 0;
		// bool isMaximizingPlayer = (depth % 2) == 0;
		// //std::cout << "depth is " << depth << std::endl;
		// game.playMove(move);

		// //game.printBoard();

		// if(game.hasWon()){
			// // std::cout << "Found winning move" << std::endl;
			// // game.printBoard();
			// game.nextPlayer();
			// if(game.hasWon()){
				// std::cout << "Wrong player's turn" << std::endl;
			// }
			// number_evaluations++;
			// if(isMaximizingPlayer){
				// //std::cout << "winning move of maximizing player" << std::endl;
				// return int(Result::win, 0, depth);
			// }
			// else{
				// return int(Result::loss, 0, depth);
				// //return int(Result::t_score, -aLot);
			// }
			// ////std::cout << "one way of winning/losing" << std::endl;
			// //number_evaluations++;
			// //return int(Result::win, depth);
		// }

		// if(game.isBoardFull()){ // && !game.hasWon()
			// number_evaluations++;
			// //game.printBoard();
			// return int(Result::t_score, 0, depth);
		// }

		// if(depth == maxDepth) {
			// number_evaluations++;
			// //game.printBoard();
			// //return game.getBoardint(depth);
			// //std::cout << "Max depth reached" << std::endl;
			// return int(Result::t_score, 0);
		// }
		// if (isMaximizingPlayer) {
			// auto possibleMoves = game.getAvailableMoves();
			// //possibleMoves.resize(2);
			// //std::cout << "Possible moves " << possibleMoves.size() << std::endl;
			// //int value = int(Result::empty_score, depth);
			// int value = negativeInf;
			// //std::cout << "possible moves in getint: " << possibleMoves.size() << std::endl;
			// game.nextPlayer();
			// for(int i = 0; i < possibleMoves.size(); i++){
				// int score = getScore(game, possibleMoves[i], alpha, beta, depth+1, maxDepth);
				// value = std::max(score, value);
				// alpha = std::max(alpha, score);
				// if(alpha >= beta){
					// //std::cout << "Breaking" << std::endl;
					// //break;
				// }
			// }
			// number_evaluations++;
			// return value;
		// }
		// else {
			// auto possibleMoves = game.getAvailableMoves();
			// //possibleMoves.resize(2);
			// //int value = int(Result::win, depth);
			// int value = positiveInf;
			// //std::cout << "possible moves in getScore: " << possibleMoves.size() << std::endl;
			// game.nextPlayer();
			// for(int i = 0; i < possibleMoves.size(); i++){
				// int score = getint(game, possibleMoves[i], alpha, beta, depth+1, maxDepth);
				// value = std::min(score, value);
				// beta = std::min(beta, score);
				// if(alpha >= beta){
					// //std::cout << "Breaking" << std::endl;
					// //break;
				// }
			// }
			// number_evaluations++;
		   //  r eturn value;
		// }
		
	}
public:
	Bot() {
		// static_assert(std::is_base_of<Game, T>::value, "Template argument of this class must derrive from Game");
		std::srand(time(nullptr)); //set the seed to the current time
	}

	template <class T, class M>
	std::vector<M> getAllBestMoves(const T game, int maxDepth){
		auto possibleMoves = game.getAvailableMoves();
		if(possibleMoves.size() == 0){
			std::cout << "no possble moves provided" << std::endl;
		}
		std::cout << "Possible move size " << possibleMoves.size() << std::endl;
		//std::cout << "Possible moves are: " << std::endl;
		//for(auto i : possibleMoves){
			//printMove(i);
		//}
		//int bestScore = int(Result::loss, 0);
		int bestScore = -100000000;
		std::vector<M> bestMoves;
		for(std::size_t i = 0; i < possibleMoves.size(); i++){
			int score = getScore<T, M>(game, possibleMoves[i], -100000000 /*alpha*/, 100000000 /*beta*/, 0, maxDepth);
			//int score = getScore(game, possibleMoves[i], int(Result::empty_score, 0) /*alpha*/, int(Result::win, 0) /*beta*/, 0, maxDepth);
			//std::cout << "Move : " << possibleMoves[i].x+1 << "	";
			// printMove(possibleMoves[i]);
			// printScore(score);
			//if(score.result == Result::win){
				//std::cout << "found winning move" << std::endl;
				//return possibleMoves[i];
			//}
			if(score == bestScore){
				bestMoves.push_back(possibleMoves[i]);
			}
			if(score > bestScore){
				//std::cout << "found better score, namely: ";
				// printScore(score);
				bestScore = score;
				bestMoves.clear();
				bestMoves.push_back(possibleMoves[i]);
			}
		}
		if(bestMoves.size() == 0) { std::cout << "error in getBestMove() " << std::endl;}
		return bestMoves;
	};
	
	template <class T, class M>
	M getBestMove(const T game, int maxDepth){
		std::vector<M> bestMoves = getAllBestMoves<T, M>(game, maxDepth);
		std::cout << "Best moves are:" << std::endl;
		for(std::size_t i = 0; i< bestMoves.size(); i++){
			// printMove(bestMoves[i]);
			bestMoves[i].print();
		}
		//std::cout << "best moves size = " << bestMoves.size() << std::endl;
		size_t random_element = rand() % bestMoves.size();
		std::cout << "Number of evalutaions: " << number_evaluations << std::endl;
		number_evaluations = 0;
		return bestMoves[random_element];
		
	}
};

