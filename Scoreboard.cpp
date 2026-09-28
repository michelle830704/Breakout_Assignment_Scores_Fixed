#include "Scoreboard.h"
#include "Play.h"
#include <string>

Scoreboard::Scoreboard() : currentScore(0) {}

void Scoreboard::drawCurrentScore(int screenWidth, int screenHeight) const {
    (void)screenWidth;
    const std::string label = "Score: " + std::to_string(currentScore);
    Play::DrawDebugText({ 100.0f, 60.0f }, label.c_str());
}

void Scoreboard::drawHighScores(HighScores& highScores) const {
    highScores.Draw();
}

void Scoreboard::incrementScore() { ++currentScore; }
void Scoreboard::resetScore() { currentScore = 0; }
