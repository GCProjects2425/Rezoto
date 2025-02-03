#include "PongScreen.h"

void PongScreen::ComputeLogic(Pong* pong)
{

    pong->MoveBall();

    // Check racket keys.
    if (IsKeyDown(KEY_Q))
        pong->MoveRacket(&pong->leftRacket, UP);
    else if (IsKeyDown(KEY_A))
        pong->MoveRacket(&pong->leftRacket, DOWN);

    if (IsKeyDown(KEY_I))
        pong->MoveRacket(&pong->rightRacket, UP);
    else if (IsKeyDown(KEY_J))
        pong->MoveRacket(&pong->rightRacket, DOWN);


    if (IsKeyPressed(KEY_ESCAPE))
        pong->SetScreen(pong->TitleScreen);
}

void PongScreen::Draw(Pong* pong)
{
    pong->Draw();
}

void PongScreen::StartScreen(Pong* pong)
{
    pong->ResetGame();
}
