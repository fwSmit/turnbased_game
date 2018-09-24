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
	Score(Result _result, int _score = 0) : result(_result), score(_score){}
};

Score operator-(const Score& input);


bool operator==(const Score& lhs, const Score& rhs);

bool operator>(const Score& lhs, const Score& rhs);

bool operator<(const Score& lhs, const Score& rhs);

void printScore(Score score);

template <class T>
class Bot{
	Score getScore(T game, Move move, int depth, const int maxDepth){
		//std::cout << "depth is " << depth << std::endl;
		game.playMove(move);

		if(game.hasWon()){
			//std::cout << "one way of winning/losing" << std::endl;
			return Score(Result::win);
		}

		if(game.isBoardFull()){ // && !game.hasWon()
			return Score(Result::draw);
		}

		if(depth == maxDepth) {return game.getBoardScore();}
		auto possibleMoves = game.getAvailableMoves();
		Score bestScore = Score(Result::win);
		//std::cout << "possible moves in getScore: " << possibleMoves.size() << std::endl;
		game.nextPlayer();
		for(int i = 0; i < possibleMoves.size(); i++){
			Score score = -getScore(game, possibleMoves[i], depth+1, maxDepth);
			bestScore = std::min(score, bestScore);
		}
		return bestScore;
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
		Score bestScore = Score(Result::loss);
		std::vector<Move> bestMoves;
		for(int i = 0; i < possibleMoves.size(); i++){
			Score score = getScore(game, possibleMoves[i], 0, maxDepth);
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
		std::cout << "best moves size = " << bestMoves.size() << std::endl;
		size_t random_element = rand() % bestMoves.size();
		return bestMoves[random_element];
	};
};

