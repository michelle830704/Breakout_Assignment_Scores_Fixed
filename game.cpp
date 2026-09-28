#include "game.h"
#include "constant.h"
#include "paddle.h"
#include "Scoreboard.h"
#include "HighScores.h"
#include "Play.h"
#include <string>

namespace {
    constexpr int ROWS = 8;
    constexpr int COLUMNS = 35;
    constexpr float BRICK_WIDTH = 15.0f;
    constexpr float BRICK_HEIGHT = 10.0f;
    constexpr float BRICK_GAP = 2.0f;
    constexpr float BRICK_START_X =
        (DISPLAY_WIDTH - (COLUMNS * BRICK_WIDTH + (COLUMNS - 1) * BRICK_GAP)) / 2.0f;
    // Play uses y = 0 at the TOP of the window.
    constexpr float BRICK_START_Y = 25.0f;
    constexpr float PADDLE_Y = DISPLAY_HEIGHT - 25.0f;
    const std::string HIGH_SCORE_FILE = "highscores.txt";

    struct Ball {
        Play::Point2D pos;
        Play::Point2D velocity;
        float radius;
    };

    Ball ball{};
    Paddle paddle{};
    Scoreboard scoreboard;
    HighScores highScores;
    bool bricks[ROWS][COLUMNS]{};
    bool scoresLoaded = false;

    bool BallHitsBrick(const Ball& b, float left, float right, float top, float bottom) {
        const float closestX = myMax(left, myMin(b.pos.x, right));
        const float closestY = myMax(top, myMin(b.pos.y, bottom));
        const float dx = b.pos.x - closestX;
        const float dy = b.pos.y - closestY;
        return dx * dx + dy * dy <= b.radius * b.radius;
    }

    bool AllBricksGone() {
        for (int row = 0; row < ROWS; ++row) {
            for (int column = 0; column < COLUMNS; ++column) {
                if (bricks[row][column]) return false;
            }
        }
        return true;
    }
}

void SpawnBall() {
    ball.pos = { DISPLAY_WIDTH / 2.0f, DISPLAY_HEIGHT - 65.0f };
    ball.velocity = { ballSpeed * 0.7f, -ballSpeed * 0.7f };
    ball.radius = radius;
}

void SetupScene() {
    if (!scoresLoaded) {
        highScores.LoadFromFile(HIGH_SCORE_FILE);
        scoresLoaded = true;
    }
    paddle.position = { DISPLAY_WIDTH / 2.0f, PADDLE_Y };
    paddle.width = 90.0f;
    paddle.height = 12.0f;
    for (int row = 0; row < ROWS; ++row) {
        for (int column = 0; column < COLUMNS; ++column) {
            bricks[row][column] = true;
        }
    }
    scoreboard.resetScore();
    SpawnBall();
}

void ResetGame() {
    highScores.AddScore(scoreboard.getCurrentScore());
    SetupScene();
}

void StepFrame(float elapsedTime) {
    UpdatePaddlePosition(paddle);
    ball.pos.x += ball.velocity.x * elapsedTime;
    ball.pos.y += ball.velocity.y * elapsedTime;

    if (ball.pos.x < ball.radius) {
        ball.pos.x = ball.radius;
        ball.velocity.x = -ball.velocity.x;
    } else if (ball.pos.x > DISPLAY_WIDTH - ball.radius) {
        ball.pos.x = DISPLAY_WIDTH - ball.radius;
        ball.velocity.x = -ball.velocity.x;
    }
    if (ball.pos.y < ball.radius) {
        ball.pos.y = ball.radius;
        ball.velocity.y = -ball.velocity.y;
    }
    if (ball.velocity.y > 0 && isCollidingWithPaddle(ball, paddle)) {
        ball.pos.y = paddle.position.y - paddle.height / 2 - ball.radius;
        ball.velocity.y = -ball.velocity.y;
    }

    bool hit = false;
    for (int row = 0; row < ROWS && !hit; ++row) {
        for (int column = 0; column < COLUMNS; ++column) {
            if (!bricks[row][column]) continue;
            const float left = BRICK_START_X + column * (BRICK_WIDTH + BRICK_GAP);
            const float top = BRICK_START_Y + row * (BRICK_HEIGHT + BRICK_GAP);
            if (BallHitsBrick(ball, left, left + BRICK_WIDTH, top, top + BRICK_HEIGHT)) {
                bricks[row][column] = false;
                ball.velocity.y = -ball.velocity.y;
                scoreboard.incrementScore();
                hit = true;
                break;
            }
        }
    }

    if (ball.pos.y > DISPLAY_HEIGHT + ball.radius || AllBricksGone()) {
        ResetGame();
    }

    for (int row = 0; row < ROWS; ++row) {
        for (int column = 0; column < COLUMNS; ++column) {
            if (!bricks[row][column]) continue;
            const float left = BRICK_START_X + column * (BRICK_WIDTH + BRICK_GAP);
            const float top = BRICK_START_Y + row * (BRICK_HEIGHT + BRICK_GAP);
            Play::DrawRect(
                { left, DISPLAY_HEIGHT - (top + BRICK_HEIGHT) },
                { left + BRICK_WIDTH, DISPLAY_HEIGHT - top },
                Play::cBlue, true);
        }
    }

    DrawPaddle(paddle);
    Play::DrawCircle(
        { ball.pos.x, DISPLAY_HEIGHT - ball.pos.y },
        static_cast<int>(ball.radius), Play::cYellow);
    scoreboard.drawCurrentScore(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    scoreboard.drawHighScores(highScores);
}

void ExitGame() {
    highScores.SaveToFile(HIGH_SCORE_FILE);
}
