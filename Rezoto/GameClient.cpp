#include "GameClient.h"

//CLIENT - (se lancera après la connexion + reception des infos par le serveur)
void GameClient::InitializeElements(void)
{
    InitWindow(800, 600, "Pong");
    // Calculate size, position and inner limits of window.
    screen = { 0, 0, (float)GetScreenWidth() , (float)GetScreenHeight()  };
    playableBorder = { CALIBER, CALIBER, screen.width - (2 * CALIBER) , screen.height - (2 * CALIBER) };
    top = { screen.x, screen.y, playableBorder.width, playableBorder.y };
    bottom = { screen.x, playableBorder.height + CALIBER, screen.width, screen.y };
    SetTargetFPS(60);
    ResetGame();
}

//SERVER COMPUTE - TRANSFERT
void GameClient::MoveBall(void)
{
    static int xx = CALIBER / 2;
    static int yy = CALIBER / 2;

    // Check collision with rackets and ball has not surpassed rackets.
    if ((CheckCollisionRecs(ball, leftRacket) && ball.x < leftRacket.x + leftRacket.width) ||
        (CheckCollisionRecs(ball, rightRacket) && ball.x > rightRacket.x - rightRacket.width))
        xx = -xx;
    else
        if (CheckCollisionRecs(ball, top) || CheckCollisionRecs(ball, bottom))
            yy = -yy;
        else
        {
            // Score.
            if (ball.x < screen.x)
            {
                ++rightScore;
                ServeBall();
            }
            else if (ball.x > screen.width)
            {
                ++leftScore;
                ServeBall();
            }
        }

    // Move ball.
    ball.x += xx;
    ball.y += yy;
}

//SERVER COMPUTE - TRANSFERT
void GameClient::MoveRacket(Rectangle* pRacket, Direction pDir)
{
    int step = (pDir == UP) ? -CALIBER / 2 : CALIBER / 2;

    if ((CheckCollisionRecs(top, *pRacket) && pDir == UP) ||
        (CheckCollisionRecs(bottom, *pRacket) && pDir == DOWN))
        return;
    pRacket->y += step;
}

//CLIENT - MODIFIER POUR CLIENT SOLO (contrôle up/down sans connaissance du côté contrôlé -> server attribue le contrôle dans le compute)
void GameClient::ComputeGameplay()
{
    MoveBall();

    // Check racket keys.
    if (IsKeyDown(KEY_Q))
        MoveRacket(&leftRacket, Direction::UP);
    else if (IsKeyDown(KEY_A))
        MoveRacket(&leftRacket, Direction::DOWN);

    if (IsKeyDown(KEY_I))
        MoveRacket(&rightRacket, Direction::UP);
    else if (IsKeyDown(KEY_J))
        MoveRacket(&rightRacket, Direction::DOWN);
}

//CLIENT
void GameClient::Draw()
{
    // Draw court.
    DrawRectangle(screen.x, screen.y, screen.width, screen.height, GRAY);
    DrawRectangle(screen.x, playableBorder.y, screen.width, playableBorder.height, BLACK);
    DrawRectangle((screen.width / 2) - 5, playableBorder.y, CALIBER, playableBorder.height, GRAY);
    // Draw score.
    DrawText(std::to_string(leftScore).c_str(), (screen.width / 2) - 50 - scoreWidth, 50, 60, GRAY);
    DrawText(std::to_string(rightScore).c_str(), (screen.width / 2) + 50, 50, 60, GRAY);

    // Draw ball.
    DrawRectangle(ball.x, ball.y, ball.width, ball.height, WHITE);
    // Draw rackets.
    DrawRectangle(leftRacket.x, leftRacket.y, leftRacket.width, leftRacket.height, WHITE);
    DrawRectangle(rightRacket.x, rightRacket.y, rightRacket.width, rightRacket.height, WHITE);
}

//SERVER COMPUTE - TRANSFERT
void GameClient::ServeBall(void)
{
    ball.x = playableBorder.width / 2;
    ball.y = GetRandomValue(playableBorder.y + 10, playableBorder.height);
}

//CLIENT
void GameClient::SetScreen(GameScreen* screen)
{
    if (screen != CurrentScreen) {
        CurrentScreen = screen;
        screen->StartScreen(this);
    }
}

//SERVER COMPUTE - TRANSFERT
void GameClient::ResetGame(void)
{
    // Initialize elements.
    ball = { 5 * CALIBER, playableBorder.height, CALIBER, CALIBER };
    leftRacket = { playableBorder.x + CALIBER, playableBorder.height / 2, CALIBER, 5 * CALIBER };
    rightRacket = { playableBorder.width - CALIBER, playableBorder.height / 2, CALIBER, 5 * CALIBER };
    scoreWidth = MeasureText("00", 60);
}

//SERVER
void GameClient::CheckScore()
{
    if ((leftScore >= 11) || (rightScore >= 11))
    {
        if (abs(leftScore - rightScore) < 2)
            return;
        winner = (leftScore > rightScore) ? 1 : 2;
        rightScore = leftScore = 0; // Reset Score.
        //TODO DO SOMETHING
        }
}
