#pragma once
#include "Game.h"
#include <iostream>
#include <vector>

class Bot{
public:
	static const int winning_score = 10000;
	static const int losing_score = -10000;
	static const int a_lot = 10*winning_score; // must be bigger than the biggest possible score
public: //private
	mutable int number_evaluations = 0;

	// depth starts at maxDepth and ends when it's equal to 0
	// maxDepth is the maximum number of nodes the algorithm may travel down. If maxDepth is zero the algoritm will immediately return a heuristic value
	template <class T, class M>
	int getScore(T game, M move, int alpha, int beta, unsigned int depth, bool isMaximizingPlayer) const{ // uses alpha beta pruning
		game.playMove(move);
		if(game.hasWon()){
			std::cout << "someone has won" << std::endl;
			if(isMaximizingPlayer){
				return winning_score;
			}
			else{
				return losing_score;
			}
		}
		if(depth == 0 || game.state.board.isFull()){
			return 0;
		}
		if(isMaximizingPlayer){ // maximizing player
			int value = -a_lot;
			game.nextPlayer();
			std::vector<M> possibleMoves = game.getAvailableMoves();
			for(std::size_t i = 0; i < possibleMoves.size(); i++){
				value = std::max(value, getScore<T, M>(game, possibleMoves[i], alpha, beta, depth-1, false));
				alpha = std::max(alpha, value);
				if(alpha >= beta){
					// std::cout << "Breaking" << std::endl;
					// break;
				}
			}
			return value;
		}
		else // minimizing player
		{
			int value = a_lot;
			game.nextPlayer();
			std::vector<M> possibleMoves = game.getAvailableMoves();
			for(std::size_t i = 0; i < possibleMoves.size(); i++){
				value = std::min(value, getScore<T, M>(game, possibleMoves[i], alpha, beta, depth-1, true));
				beta = std::min(beta, value);
				if(alpha >= beta){
					// std::cout << "Breaking" << std::endl;
					// break;
				}
			}
			return value;
		}
	}
public:
	Bot() {
		// static_assert(std::is_base_of<Game, T>::value, "Template argument of this class must derrive from Game");
		std::srand(time(nullptr)); //set the seed to the current time
	}

	template <class T, class M>
	std::vector<M> getAllBestMoves(const T game, int maxDepth) const{
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
		int bestScore = -a_lot;
		std::vector<M> bestMoves;
		for(std::size_t i = 0; i < possibleMoves.size(); i++){
			int score = getScore<T, M>(game, possibleMoves[i], -a_lot /*alpha*/, a_lot /*beta*/, maxDepth, true);
			//if(score.result == Result::win){
				//std::cout << "found winning move" << std::endl;
				//return possibleMoves[i];
			//}
			if(score == bestScore){
				// std::cout << "same score" << std::endl;
				bestMoves.push_back(possibleMoves[i]);
			}
			if(score > bestScore){
				std::cout << "improvement" << std::endl;
				std::cout << "score is now: " << score << std::endl;
				bestScore = score;
				bestMoves.clear();
				bestMoves.push_back(possibleMoves[i]);
			}
		}
		if(bestMoves.size() == 0) { std::cout << "error in getBestMove() " << std::endl;}
		return bestMoves;
	};

	template <class T, class M>
	M getBestMove(const T game, int maxDepth) const{
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

