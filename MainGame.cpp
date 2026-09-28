#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "game.h"
#include "constant.h"

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE) {
    Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
    Play::CentreAllSpriteOrigins();
    SetupScene();
}

bool MainGameUpdate(float elapsedTime) {
    Play::ClearDrawingBuffer(Play::cBlack);
    StepFrame(elapsedTime);
    Play::PresentDrawingBuffer();

    return Play::KeyDown(Play::KEY_ESCAPE);
}

int MainGameExit() {
    ExitGame();
    Play::DestroyManager();
    return PLAY_OK;
}