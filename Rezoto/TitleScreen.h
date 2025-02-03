#pragma once
#include "GameScreen.h"
#include "pong.h"

class TitleScreen : public GameScreen
{
    void ComputeLogic(Pong* pong) override;
    void Draw(Pong* pong) override;
    void StartScreen(Pong* pong) override;
};
