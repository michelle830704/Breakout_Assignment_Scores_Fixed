#pragma once
#include "Play.h"

struct Paddle {
    Play::Point2D position;
    float width;
    float height;
};

void DrawPaddle(const Paddle& paddle);
void UpdatePaddlePosition(Paddle& paddle);

// Our own versions of min and max using ternary operators.
inline float myMin(float a, float b) {
    return (a < b) ? a : b;
}

inline float myMax(float a, float b) {
    return (a > b) ? a : b;
}

template <typename BallType>
bool isCollidingWithPaddle(const BallType& ball, const Paddle& paddle) {
    const float left = paddle.position.x - paddle.width / 2;
    const float right = paddle.position.x + paddle.width / 2;
    const float top = paddle.position.y - paddle.height / 2;
    const float bottom = paddle.position.y + paddle.height / 2;

    // Find the point on the paddle closest to the ball.
    const float closestX = myMax(left, myMin(ball.pos.x, right));
    const float closestY = myMax(top, myMin(ball.pos.y, bottom));

    const float dx = ball.pos.x - closestX;
    const float dy = ball.pos.y - closestY;

    return (dx * dx + dy * dy) <= (ball.radius * ball.radius);
}