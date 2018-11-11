#include "Bot.h"
#include <gtest/gtest.h>

TEST(scoreComparisonTest, lessThan){
	Score negative(-12);
	Score positive(24);
	//bool less_true = negative < positive;
	//bool less_false = positive < negative;
	//EXPECT_EQ(less_true, true);
	//EXPECT_EQ(less_false, false);
	EXPECT_EQ(negative.score, -11);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
