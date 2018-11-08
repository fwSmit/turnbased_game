#include "Bot.h"


Score operator-(const Score& input){
	Score _score = input;
	if(_score.result == Result::win){
		_score.result = Result::loss;
		return _score;
	}
	if(_score.result == Result::loss){
		_score.result = Result::win;
		return _score;
	}
	if(_score.result == Result::t_score){
		_score.score = -_score.score;
	}
	return _score;
}

bool operator==(const Score& lhs, const Score& rhs){
	return lhs.result == rhs.result && lhs.score == rhs.score;
}

// yet has to take depth into account
bool operator>(const Score& lhs, const Score& rhs){
	if (rhs.result == Result::empty_score) {
		return true;
	}
	if (lhs.result == Result::empty_score) {
		return false;
	}
	assert(lhs.result != Result::empty_score && rhs.result != Result::empty_score);

	if(rhs.result == Result::win){
		return false;
	}
	if(lhs.result == Result::win){ 
		 return true;
	 }
	if(lhs.result == Result::loss) {return false;}
	if(rhs.result == Result::loss) {return true;}
	if(lhs.result == Result::t_score) {
		 if(rhs.result == Result::t_score){
			 return lhs.score > rhs.score;
		 }
		 // rhs must be draw
		 if(lhs.score > 0){
			 return true;
		 }
		 else{
			 return false;
		 }
	}
	if(lhs.result == Result::draw){
		if(rhs.result == Result::t_score){
			if(rhs.score < 0) {
				return true;
			}
			else {
				return false;
			}
		}
		if(rhs.result == Result::draw){
			return false;
		}
	}

	assert(0); // shouldnt reach this point
	return false;
}

bool operator<(const Score& lhs, const Score& rhs){
	return rhs > lhs;
}

void printScore(Score score){
	if(score.result == Result::t_score){
		std::cout << "score is " << score.score << std::endl;
	}
	else{
		if(score.result == Result::win){
			std::cout << "winning score" << std::endl;
		}else if(score.result == Result::loss) {
			std::cout << "losing score" << std::endl;
		}
	}
}
