#include "Party.h"
#include <cstdlib>
#include <ctime>
#include <raylib.h>

Party::Party() 
{
	m_ID = rand();

    m_Screen = { 0, 0, 800 , 600 };
    m_PlayableBorder = { CALIBER, CALIBER, m_Screen.width - (2 * CALIBER) , m_Screen.height - (2 * CALIBER) };
    m_Top = { m_Screen.x, m_Screen.y, m_PlayableBorder.width, m_PlayableBorder.y };
    m_Bottom = { m_Screen.x, m_PlayableBorder.height + CALIBER, m_Screen.width, m_Screen.y };

    SetTargetFPS(60);
}

void Party::ComputeGame()
{
	ComputeBallPos();
}

void Party::ComputeBallPos()
{
    static int xx = CALIBER / 2;
    static int yy = CALIBER / 2;

    // Check collision with rackets and ball has not surpassed rackets.
    if ((CheckCollisionRecs(m_Ball.ToRectangle(), m_LeftRacket.ToRectangle()) && m_Ball.x < m_LeftRacket.x + m_LeftRacket.width) ||
        (CheckCollisionRecs(m_Ball.ToRectangle(), m_RightRacket.ToRectangle()) && m_Ball.x > m_RightRacket.x - m_RightRacket.width))
        xx = -xx;
    else
        if (CheckCollisionRecs(m_Ball.ToRectangle(), m_Top.ToRectangle()) || CheckCollisionRecs(m_Ball.ToRectangle(), m_Bottom.ToRectangle()))
            yy = -yy;
        else
        {
            // Score.
            if (m_Ball.x < m_Screen.x)
            {
                ++rightScore;
                ServeBall();
            }
            else if (m_Ball.x > m_Screen.width)
            {
                ++leftScore;
                ServeBall();
            }
        }

    // Move ball.
    m_Ball.x += xx;
    m_Ball.y += yy;
}

void Party::ComputeRacketPos(LeRectangle* pRacket, Direction pDir)
{
    int step = (pDir == UP) ? -CALIBER / 2 : CALIBER / 2;

    if ((CheckCollisionRecs(m_Top.ToRectangle(), pRacket->ToRectangle()) && pDir == UP) ||
        (CheckCollisionRecs(m_Bottom.ToRectangle(), pRacket->ToRectangle()) && pDir == DOWN))
        return;
    pRacket->y += step;
}

void Party::ServeBall()
{
    m_Ball.x = m_PlayableBorder.width / 2;
    m_Ball.y = GetRandomValue(m_PlayableBorder.y + 10, m_PlayableBorder.height);
    
    //TODO SEND BALL POSITION
}

void Party::CheckWinner()
{
    if ((m_iLeftScore >= m_iPointsToWin) || (m_iRightScore >= m_iPointsToWin))
    {
        if (abs(m_iLeftScore - m_iRightScore) < 2)
            return;
        m_iWinner = (m_iLeftScore > m_iRightScore) ? 1 : 2;

        //TODO SEND WINNER INFO
    }
}

void Party::ResetGame()
{
    m_Ball = { 5 * CALIBER, m_PlayableBorder.height, CALIBER, CALIBER };
    m_LeftRacket = { m_PlayableBorder.x + CALIBER, m_PlayableBorder.height / 2, CALIBER, 5 * CALIBER };
    m_RightRacket = { m_PlayableBorder.width - CALIBER, m_PlayableBorder.height / 2, CALIBER, 5 * CALIBER };

    m_iRightScore = 0;
    m_iLeftScore = 0;
    m_iWinner = 0;
}
