#include "Bot.h"
#include "Bot.cpp"
#include <gtest/gtest.h>

void testOrder(const std::vector<Score>& input);

TEST(scoreComparisonTest, scoreOnly){
	Score negative(Result::t_score, -12);
	Score moreNegative(Result::t_score, -122);
	Score neutral(Result::t_score, 0);
	Score positive(Result::t_score, 24);
	//EXPECT_EQ(negative.score, -12);
	//EXPECT_LT(negative, positive);
	//EXPECT_LT(moreNegative, negative);
	//EXPECT_GT(positive, negative);
	std::vector<Score> order{moreNegative, negative, neutral, positive};
	testOrder(order);
}

TEST(scoreComparisonTest, winLossScore){
	Score win(Result::win, 0);
	Score loss(Result::loss, 0);
	Score positiveScore(Result::t_score, 12);
	Score neutralScore(Result::t_score, 0);
	Score negativeScore(Result::t_score, -12);
	std::vector<Score> order{loss, negativeScore, neutralScore, positiveScore, win};
	testOrder(order);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void testOrder(const std::vector<Score>& input){
	ASSERT_GT(input.size(), 1);
	for(int i = 0; i < input.size()-1; i++){
		for(int j = i+1; j < input.size(); j++){
			//std::cout << i << " " << j << std::endl;
			EXPECT_LT(input[i], input[j]);
			EXPECT_GT(input[j], input[i]);
		}
	}
}
