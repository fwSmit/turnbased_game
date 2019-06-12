#include "Bot.h"
#include "Bot.cpp"
#include "tictactoe.h"
#include "tictactoe.cpp"
#include "Game.h"
#include "Game.cpp"
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

TEST(scoreComparisonTest, depthTest){
	Score win(Result::win, 0);
	Score winMoreDepth(Result::win, 0);
	winMoreDepth.depth = 10;
	Score loss(Result::loss, 0);
	Score lossMoreDepth(Result::loss, 0);
	lossMoreDepth.depth = 10;
	Score positiveScore(Result::t_score, 12);
	Score neutralScore(Result::t_score, 0);
	Score negativeScore(Result::t_score, -12);
	std::vector<Score> order{loss, lossMoreDepth, negativeScore, neutralScore, positiveScore, winMoreDepth, win};
	testOrder(order);
}
TEST(botTest, onePossible){
	tictactoe game(true, false, true);
	game.playMove(Move(2, 2));
	game.nextPlayer();
	game.playMove(Move(1, 1));
	game.nextPlayer();
	game.playMove(Move(0, 0));
	//game.getBotMove();
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
