#pragma once
#include "GameScreen.h"
#include "pong.h"
class PongScreen :
    public GameScreen
{
    void ComputeLogic(Pong* pong) override;
    void Draw(Pong* pong) override;
    void StartScreen(Pong* pong) override;
};

