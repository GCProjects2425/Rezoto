#pragma once
#include <string>
#include <vector>
#include "CustomStruct.h"

struct Player
{
	std::string ip;
	std::string username;
	time_t connectionStart;
	time_t lastPing;
	int port;

	Player() : ip(""), username(""), port(0), connectionStart(0), lastPing(0) {}
	Player(const std::string& ip, const std::string& username, int port) : ip(ip), username(username), port(port) 
	{
		connectionStart = time(0);
		lastPing = connectionStart;
	}
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

	LeVector2 GetBallPos() { return m_BallPos; }
	LeVector2 GetLeftRacketPos() { return m_LeftRacketPos; }
	LeVector2 GetRightRacketPos() { return m_RightRacketPos; }

	int GetLeftScore() { return m_iLeftScore; }
	int GetRightScore() { return m_iRightScore; }
	int GetWinner() { return m_iWinner; }

	std::vector<Player*> GetPlayerList() { return m_vPlayerList; }
	void AddPlayer(Player* pPlayer) { m_vPlayerList.push_back(pPlayer); }

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
	LeVector2 m_LeftRacketPos;
	LeVector2 m_RightRacketPos;

	Direction m_LeftRacketDir, m_RightRacketDir;

	void ComputeBallPos();
	void ComputeRacketPos(LeRectangle* pRacket, Direction pDir);

	void ServeBall();
	void CheckWinner();
	void ResetGame();
};

