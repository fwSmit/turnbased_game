#pragma once
#include "Game.h"
#include <iostream>
#include <vector>
#include <limits>
#include <assert.h>

enum Result{win, loss, draw, empty_score, t_score /*some score is calculated*/};

struct Score{
	Result result;
	int score;
	unsigned int depth;
	Score(Result _result, unsigned int depth, int _score = 0) : result(_result), score(_score){}
};

Score operator-(const Score& input);


bool operator==(const Score& lhs, const Score& rhs);

bool operator>(const Score& lhs, const Score& rhs);

bool operator<(const Score& lhs, const Score& rhs);

void printScore(Score score);

template <class T>
class Bot{
	int number_evaluations = 0;
	// depth starts at 0 and ends when it's equal to maxDepth (0 <= depth <= maxDepth)
	// maxDepth is the maximum number of nodes the algorithm may travel down. If maxDepth is zero the algoritm will immediately return a value
	Score getScore(T game, Move move, Score alpha, Score beta, unsigned int depth, const unsigned int maxDepth){
		bool isMaximizingPlayer = (depth % 2) == 0;
		//std::cout << "depth is " << depth << std::endl;
		game.playMove(move);
		if(game.hasWon()){
			number_evaluations++;
			if(isMaximizingPlayer){
				//std::cout << "winning move of maximizing player" << std::endl;
				return Score(Result::win, depth);
			}
			else{
				return Score(Result::loss, depth);
			}
			////std::cout << "one way of winning/losing" << std::endl;
			//number_evaluations++;
			//return Score(Result::win, depth);
		}

		if(game.isBoardFull()){ // && !game.hasWon()
			number_evaluations++;
			return Score(Result::draw, depth);
		}

		if(depth == maxDepth) {
			number_evaluations++;
			return game.getBoardScore(depth);
		}
		if (isMaximizingPlayer) {
			auto possibleMoves = game.getAvailableMoves();
			Score value = Score(Result::empty_score, depth);
			//std::cout << "possible moves in getScore: " << possibleMoves.size() << std::endl;
			game.nextPlayer();
			for(int i = 0; i < possibleMoves.size(); i++){
				Score score = getScore(game, possibleMoves[i], alpha, beta, depth+1, maxDepth);
				value = std::max(score, value);
				alpha = std::max(alpha, score);
				if(alpha > beta){
					std::cout << "Breaking" << std::endl;
					break;
				}
			}
			number_evaluations++;
			return value;
		}
		else {
			auto possibleMoves = game.getAvailableMoves();
			Score value = Score(Result::empty_score, depth);
			//std::cout << "possible moves in getScore: " << possibleMoves.size() << std::endl;
			game.nextPlayer();
			for(int i = 0; i < possibleMoves.size(); i++){
				Score score = getScore(game, possibleMoves[i], alpha, beta, depth+1, maxDepth);
				value = std::min(score, value);
				beta = std::min(beta, score);
				if(alpha > beta){
					std::cout << "Breaking" << std::endl;
					break;
				}
			}
			number_evaluations++;
			return value;
		}
		
	}
public:
	Bot(){
		std::srand(time(nullptr)); //set the seed to the current time
	}

	
	Move getBestMove(const T game, int maxDepth){
		auto possibleMoves = game.getAvailableMoves();
		if(possibleMoves.size() == 0){
			std::cout << "no possble moves provided" << std::endl;
		}
		std::cout << "Possible move size " << possibleMoves.size() << std::endl;
		Score bestScore = Score(Result::loss, 0);
		std::vector<Move> bestMoves;
		for(int i = 0; i < possibleMoves.size(); i++){
			Score score = getScore(game, possibleMoves[i], Score(Result::empty_score, 0) /*alpha*/, Score(Result::win, 0) /*beta*/, 0, maxDepth);
			std::cout << "Move : " << possibleMoves[i].x+1 << "	";
			printScore(score);
			if(score.result == Result::win){
				std::cout << "found winning move" << std::endl;
				return possibleMoves[i];
			}
			if(score == bestScore){
				bestMoves.push_back(possibleMoves[i]);
			}
			if(score > bestScore){
				//std::cout << "found better score, namely: " << score.score << std::endl;
				bestScore = score;
				bestMoves.clear();
				bestMoves.push_back(possibleMoves[i]);
			}
		}
		if(bestMoves.size() == 0) { std::cout << "error in getBestMove() " << std::endl;}
		//std::cout << "best moves size = " << bestMoves.size() << std::endl;
		size_t random_element = rand() % bestMoves.size();
		std::cout << "Number of evalutaions: " << number_evaluations << std::endl;
		number_evaluations = 0;
		return bestMoves[random_element];
	};
};

