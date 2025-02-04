#pragma once
#include "GameScreen.h"
#include "GameClient.h"

class TitleScreen : public GameScreen
{
    void ComputeLogic(GameClient* gameClient) override;
    void Draw(GameClient* gameClient) override;
    void StartScreen(GameClient* gameClient) override;
};
