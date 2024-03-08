#include "../src/Score.h"
#include <gtest/gtest.h>

TEST(Score, increase_score)
{
    Sound sound;
    Score score = Score(&sound);

    int previousScore = 0;

    score.increase_score(E_TYPE);
    EXPECT_EQ(previousScore + 70, score.score);
    previousScore = score.score;

    score.increase_score(P_TYPE);
    EXPECT_EQ(previousScore + 60, score.score);
    previousScore = score.score;

    score.increase_score(I_TYPE);
    EXPECT_EQ(previousScore + 50, score.score);
    previousScore = score.score;


    score.increase_score(ASTEROID);
    EXPECT_EQ(previousScore + 10, score.score);
    previousScore = score.score;

    score.increase_score(MINE);
    EXPECT_EQ(previousScore + 20, score.score);
    previousScore = score.score;

    score.increase_score(SPACE_STATION);
    EXPECT_EQ(previousScore + 1500, score.score);
    previousScore = score.score;

    score.increase_score(CANNON);
    EXPECT_EQ(previousScore + 200, score.score);
    previousScore = score.score;

    while(score.score < score.highscore)
    {
        score.increase_score(SPACE_STATION);
    }

    score.increase_score(SPACE_STATION);
    EXPECT_EQ(score.highscore, score.score);

    while(score.score < 99999999)
    {
        score.increase_score(SPACE_STATION);
    }

    score.increase_score(SPACE_STATION);
    EXPECT_EQ(99999999, score.score);
    EXPECT_EQ(score.highscore, 99999999);


}
