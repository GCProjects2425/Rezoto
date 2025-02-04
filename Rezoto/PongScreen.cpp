#include "PongScreen.h"

void PongScreen::ComputeLogic(GameClient* gameClient)
{
    gameClient->MoveBall();

    // Check racket keys.
    if (IsKeyDown(KEY_Q))
        gameClient->MoveRacket(&gameClient->leftRacket, UP);
    else if (IsKeyDown(KEY_A))
        gameClient->MoveRacket(&gameClient->leftRacket, DOWN);

    if (IsKeyDown(KEY_I))
        gameClient->MoveRacket(&gameClient->rightRacket, UP);
    else if (IsKeyDown(KEY_J))
        gameClient->MoveRacket(&gameClient->rightRacket, DOWN);


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
