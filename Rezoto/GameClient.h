#pragma once
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameScreen.h"

#define CALIBER 12

// User-defined types.
typedef enum Direction { UP = 0, DOWN } Direction;

class GameClient
{

public:

	GameClient() {};

	// Global variables. They are global indeed.
	GameScreen* CurrentScreen;

	GameScreen* PongScreen;
	GameScreen* TitleScreen;
	GameScreen* ConnectionRoom;

	Rectangle screen, playableBorder, top, bottom, ball, leftRacket, rightRacket;
	int rightScore, leftScore, scoreWidth, winner;

	// Prototypes.
	void InitializeElements();
	void ServeBall();
	void SetScreen(GameScreen* screen);

	void ResetGame();
	void CheckScore();

	void MoveBall();
	void MoveRacket(Rectangle* pRacket, Direction pDir); 
	void ComputeGameplay();
	void Draw();

	void ComputeGameplayScreen();
};

