#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameScreen.h"
#include "Singleton.h"

#include "PongScreen.h"
#include "TitleScreen.h"
#include "ConnectionRoom.h"

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

	LeRectangle screen, playableBorder, top, bottom, ball, leftRacket, rightRacket;
	int rightScore, leftScore, scoreWidth, winner;

	// Prototypes.
	void InitializeElements();
	void ServeBall();
	void SetScreen(GameScreen* screen);

	void ResetGame();
	void CheckScore();

	void MoveBall();
	void MoveRacket(LeRectangle* pRacket, Direction pDir); 
	void ComputeGameplay();
	void Draw();

	int Run();

	void ComputeGameplayScreen();
};

