#include "PongScreen.h"

#include "GameClient.h"

#include <raylib.h>

void PongScreen::ComputeLogic(GameClient* gameClient)
{
    gameClient->MoveBall();


    if (IsKeyPressed(KEY_ESCAPE))
        gameClient->SetScreen(gameClient->TitleScreen);
}

void PongScreen::Draw(GameClient* gameClient)
{
    gameClient->Draw();
}

void PongScreen::StartScreen(GameClient* gameClient)
{
    gameClient->ResetGame();
}
