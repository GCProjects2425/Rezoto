#include "GameClient.h"

#include <raylib.h>

GameClient::GameClient()
{
    PongScreen = new class PongScreen;
    TitleScreen = new class TitleScreen;
	ConnectionRoom = new class ConnectionRoom;
}

//CLIENT - (se lancera apr�s la connexion + reception des infos par le serveur)
void GameClient::InitializeElements(void)
{
    InitWindow(800 , 600, "Pong");
    // Calculate size, position and inner limits of window.
    m_Screen = { 0, 0, (float)GetScreenWidth() , (float)GetScreenHeight()  };
    m_PlayableBorder = { CALIBER, CALIBER, m_Screen.width - (2 * CALIBER) , m_Screen.height - (2 * CALIBER) };
    /*top = { screen.x, screen.y, playableBorder.width, playableBorder.y };
    bottom = { screen.x, playableBorder.height + CALIBER, screen.width, screen.y };*/
	m_Ball = { 0, 0, CALIBER, CALIBER };
	m_LeftRacket = { m_PlayableBorder.x + CALIBER, m_PlayableBorder.height / 2, CALIBER, 5 * CALIBER };
	m_RightRacket = { m_PlayableBorder.width - CALIBER, m_PlayableBorder.height / 2, CALIBER, 5 * CALIBER };

    SetTargetFPS(60);
    ResetGame();
}

//SERVER COMPUTE - TRANSFERT
void GameClient::MoveBall(void)
{
    //static int xx = CALIBER / 2;
    //static int yy = CALIBER / 2;

    //// Check collision with rackets and ball has not surpassed rackets.
    //if ((CheckCollisionRecs(ball.ToRectangle(), leftRacket.ToRectangle()) && ball.x < leftRacket.x + leftRacket.width) ||
    //    (CheckCollisionRecs(ball.ToRectangle(), rightRacket.ToRectangle()) && ball.x > rightRacket.x - rightRacket.width))
    //    xx = -xx;
    //else
    //    if (CheckCollisionRecs(ball.ToRectangle(), top.ToRectangle()) || CheckCollisionRecs(ball.ToRectangle(), bottom.ToRectangle()))
    //        yy = -yy;
    //    else
    //    {
    //        // Score.
    //        if (ball.x < screen.x)
    //        {
    //            ++rightScore;
    //            ServeBall();
    //        }
    //        else if (ball.x > screen.width)
    //        {
    //            ++leftScore;
    //            ServeBall();
    //        }
    //    }

    //// Move ball.
    //ball.x += xx;
    //ball.y += yy;
}

//SERVER COMPUTE - TRANSFERT
void GameClient::MoveRacket(LeRectangle* pRacket, Direction pDir)
{
    /*int step = (pDir == UP) ? -CALIBER / 2 : CALIBER / 2;

    if ((CheckCollisionRecs(top.ToRectangle(), pRacket->ToRectangle()) && pDir == UP) ||
        (CheckCollisionRecs(bottom.ToRectangle(), pRacket->ToRectangle()) && pDir == DOWN))
        return;
    pRacket->y += step;*/
}

void GameClient::SendInput()
{
    //MoveBall();

    //// Check racket keys.
    //if (IsKeyDown(KEY_Q))
    //    MoveRacket(&leftRacket, Direction::UP);
    //else if (IsKeyDown(KEY_A))
    //    MoveRacket(&leftRacket, Direction::DOWN);

    //if (IsKeyDown(KEY_I))
    //    MoveRacket(&rightRacket, Direction::UP);
    //else if (IsKeyDown(KEY_J))
    //    MoveRacket(&rightRacket, Direction::DOWN);
}

//CLIENT
void GameClient::Draw()
{
    // Draw court.
    DrawRectangle(m_Screen.x, m_Screen.y, m_Screen.width, m_Screen.height, GRAY);
    DrawRectangle(m_Screen.x, m_PlayableBorder.y, m_Screen.width, m_PlayableBorder.height, BLACK);
    DrawRectangle((m_Screen.width / 2) - 5, m_PlayableBorder.y, CALIBER, m_PlayableBorder.height, GRAY);

    // Draw score.
    m_iScoreWidth = MeasureText(std::to_string(m_iLeftScore).c_str(), 60);
    DrawText(std::to_string(m_iLeftScore).c_str(), (m_Screen.width / 2) - 50 - m_iScoreWidth, 50, 60, GRAY);
    DrawText(std::to_string(m_iRightScore).c_str(), (m_Screen.width / 2) + 50, 50, 60, GRAY);

    // Draw ball.
    DrawRectangle(m_Ball.x, m_Ball.y, m_Ball.width, m_Ball.height, WHITE);
    // Draw rackets.
    DrawRectangle(m_LeftRacket.x, m_LeftRacket.y, m_LeftRacket.width, m_LeftRacket.height, WHITE);
    DrawRectangle(m_RightRacket.x, m_RightRacket.y, m_RightRacket.width, m_RightRacket.height, WHITE);
}

void GameClient::ComputeStatus(GameStatus status)
{
    m_Ball.x = status.m_BallPos.x;
    m_Ball.y = status.m_BallPos.y;

    m_RightRacket.x = status.m_RightRacketPos.x;
    m_RightRacket.y = status.m_RightRacketPos.y;

    m_LeftRacket.x = status.m_LeftRacketPos.x;
    m_LeftRacket.y = status.m_LeftRacketPos.y;
}

//CLIENT
int GameClient::Run()
{
    SetScreen(TitleScreen);
    InitializeElements();


    //Remove the possibility to close with Escape
    SetExitKey(KEY_NULL);


    // Main loop.
    while (!WindowShouldClose()) // Check ESC key.
    {
        /*if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);*/

        CurrentScreen->ComputeLogic(this);

        // Rendering.
        BeginDrawing();
        CurrentScreen->Draw(this);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}

void GameClient::ComputeGameplayScreen(GameStatus gs)
{
    m_Ball.x = gs.m_BallPos.x;
    m_Ball.y = gs.m_BallPos.y;

    m_RightRacket.x = gs.m_RightRacketPos.x;
    m_RightRacket.y = gs.m_RightRacketPos.y;

    m_LeftRacket.x = gs.m_LeftRacketPos.x;
    m_LeftRacket.y = gs.m_LeftRacketPos.y;

}

//SERVER COMPUTE - TRANSFERT
void GameClient::ServeBall(void)
{
    /*ball.x = playableBorder.width / 2;
    ball.y = GetRandomValue(playableBorder.y + 10, playableBorder.height);*/
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
    /*ball = { 5 * CALIBER, playableBorder.height, CALIBER, CALIBER };
    leftRacket = { playableBorder.x + CALIBER, playableBorder.height / 2, CALIBER, 5 * CALIBER };
    rightRacket = { playableBorder.width - CALIBER, playableBorder.height / 2, CALIBER, 5 * CALIBER };*/
    /*m_iScoreWidth = MeasureText("00", 60);*/
}

//SERVER
void GameClient::CheckScore()
{
    //if ((m_iLeftScore >= 11) || (m_iRightScore >= 11))
    //{
    //    if (abs(m_iLeftScore - m_iRightScore) < 2)
    //        return;
    //    m_iWinner = (m_iLeftScore > m_iRightScore) ? 1 : 2;
    //    m_iRightScore = m_iLeftScore = 0; // Reset Score.
    //    //TODO DO SOMETHING
    //    }
}
