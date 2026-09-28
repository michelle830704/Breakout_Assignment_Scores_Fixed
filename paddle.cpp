#include "paddle.h"
#include "constant.h"

void DrawPaddle(const Paddle& paddle) {
    Play::Point2D topLeft(
        paddle.position.x - paddle.width / 2,
        DISPLAY_HEIGHT - (paddle.position.y + paddle.height / 2)
    );

    Play::Point2D bottomRight(
        paddle.position.x + paddle.width / 2,
        DISPLAY_HEIGHT - (paddle.position.y - paddle.height / 2)
    );

   
    Play::DrawRect(topLeft, bottomRight, Play::cBlue, true);
}

void UpdatePaddlePosition(Paddle& paddle) {
    const float paddleSpeed = 4.0f;

    if (Play::KeyDown(Play::KEY_LEFT))
        paddle.position.x -= paddleSpeed;

    if (Play::KeyDown(Play::KEY_RIGHT))
        paddle.position.x += paddleSpeed;

    if (paddle.position.x - paddle.width / 2 < 0)
        paddle.position.x = paddle.width / 2;

    if (paddle.position.x + paddle.width / 2 > DISPLAY_WIDTH)
        paddle.position.x = DISPLAY_WIDTH - paddle.width / 2;
}