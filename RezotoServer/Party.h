#pragma once
#include <string>
#include <vector>
#include "CustomStruct.h"

struct Player
{
	std::string ip;
	std::string username;
	int connectionStart;
};

enum GameState
{
	IDLE,
	PAUSE,
	PLAY
};

#define CALIBER 12
// User-defined types.
typedef enum Direction { UP = 0, DOWN } Direction;

class Party
{
public:
	Party();

	int GetID() const { return m_ID; }
	void ComputeGame();
private:
	//Room variables
	std::vector<Player*> m_vPlayerList;
	int m_ID;

	//Game variables
	LeRectangle m_Screen, m_PlayableBorder, m_Top, m_Bottom, m_Ball, m_LeftRacket, m_RightRacket;
	int m_iRightScore, m_iLeftScore, m_iWinner;
	int m_iPointsToWin = 11;

	LeVector2 m_BallPos;
	LeVector2 m_PlayerPos1;
	LeVector2 m_PlayerPos2;

	void ComputeBallPos();
	void ComputeRacketPos(LeRectangle* pRacket, Direction pDir);

	void ServeBall();
	void CheckWinner();
	void ResetGame();
};

