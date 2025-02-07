#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameScreen.h"
#include "UIManager.h"
#include "Singleton.h"

#include "PongScreen.h"
#include "TitleScreen.h"
#include "ConnectionRoom.h"
#include "GameStatus.h"

#define CALIBER 12

// User-defined types.
typedef enum Direction { UP = 0, DOWN } Direction;

class GameClient : public Singleton<GameClient>
{
	friend class Singleton<GameClient>;
public:

	GameClient();

	// Global variables. They are global indeed.
	GameScreen* CurrentScreen;

	PongScreen* PongScreen;
	TitleScreen* TitleScreen;
	ConnectionRoom* ConnectionRoom;

	LeRectangle m_Screen, m_PlayableBorder, m_Ball, m_LeftRacket, m_RightRacket;
	int m_iRightScore, m_iLeftScore, m_iScoreWidth, m_iWinner;

	// Prototypes.
	void InitializeElements();
	void ServeBall();
	void SetScreen(GameScreen* screen);

	void ResetGame();
	void CheckScore();

	void MoveBall();
	void MoveRacket(LeRectangle* pRacket, Direction pDir); 
	void SendInput();
	void Draw();

	void ComputeStatus(GameStatus status);

	int Run();

	void ComputeGameplayScreen(GameStatus gs);
};

