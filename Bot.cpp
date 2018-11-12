#include "Bot.h"


//Score operator-(const Score& input){
	//Score _score = input;
	//if(_score.result == Result::win){
		//_score.result = Result::loss;
		//return _score;
	//}
	//if(_score.result == Result::loss){
		//_score.result = Result::win;
		//return _score;
	//}
	//if(_score.result == Result::t_score){
		//_score.score = -_score.score;
	//}
	//return _score;
//}

bool operator==(const Score& lhs, const Score& rhs){
	return lhs.result == rhs.result && lhs.score == rhs.score;
}
//bool operator==(const Score& lhs, const Score& rhs){
	//return lhs.score == rhs.score;
//}

//bool operator>(const Score& lhs, const Score& rhs){
	//return lhs.score > rhs.score;
//}

// yet has to take depth into account
bool operator>(const Score& lhs, const Score& rhs){
	//if (rhs.result == Result::empty_score) {
		//return true;
	//}
	//if (lhs.result == Result::empty_score) {
		//return false;
	//}
	assert(lhs.result != Result::empty_score && rhs.result != Result::empty_score);

	if(rhs.result == Result::positiveInf){
		return false;
	}
	if(lhs.result == Result::positiveInf){
		return true;
	}
	if(lhs.result == Result::negativeInf){
		return false;
	}
	if(rhs.result == Result::negativeInf){
		return true;
	}

	if(rhs.result == Result::win){
		return false;
	}
	if(lhs.result == Result::win){ 
		 return true;
	 }
	if(lhs.result == Result::loss) {
		return false;
	}
	if(rhs.result == Result::loss) {
		return true;
	}
	if(lhs.result == Result::t_score) {
		 if(rhs.result == Result::t_score){
			 return lhs.score > rhs.score;
		 }
		 //if(lhs.score > 0){
			 //return true;
		 //}
		 //else{
			 //return false;
		 //}
	}
	assert(0); // shouldnt reach this point
	return false;
}

bool operator<(const Score& lhs, const Score& rhs){
	return rhs > lhs;
}
bool operator>=(const Score& lhs, const Score& rhs){
	return !(lhs > rhs);
}

void printMove(Move move){
	std::cout << "(" <<  move.x+1 << ", " << move.y+1 << ") ";
}
void printScore(Score score){
	//std::cout << "score is " << score.score << std::endl;
	if(score.result == Result::t_score){
		std::cout << "score is " << score.score;
	}else if(score.result == Result::win){
		std::cout << "winning score";
	}else if(score.result == Result::loss) {
		std::cout << "losing score";
	}else if(score.result == Result::negativeInf){
		std::cout << "negative infinity";
	}else if(score.result == Result::positiveInf){
		std::cout << "positive infinity";
	}else if(score.result == empty_score){
		std::cout<< "empty score";
	}
	std::cout << ", depth " << score.depth << std::endl;
}
