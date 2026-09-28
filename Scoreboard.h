#pragma once
#include "HighScores.h"

class Scoreboard {
private:
    unsigned int currentScore;

public:
    Scoreboard();

    void drawCurrentScore(int screenWidth, int screenHeight) const;
    void drawHighScores(HighScores& highScores) const;

    void incrementScore();
    void resetScore();

    unsigned int getCurrentScore() const { return currentScore; }
};
