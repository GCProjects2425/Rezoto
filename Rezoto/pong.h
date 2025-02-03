#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "string"

#define CALIBER 12

#pragma once

// User-defined types.
typedef enum GameScreen { TITLE = 0, GAMEPLAY, ENDING } GameScreen;
typedef enum Direction { UP = 0, DOWN } Direction;

class Pong
{

public:

	Pong() {};

	// Global variables. They are global indeed.
	Rectangle screen, playableBorder, top, bottom, ball, leftRacket, rightRacket;
	int rightScore = 0, leftScore = 0, scoreWidth, winner;

	// Prototypes.
	void InitializeElements(void);
	void ServeBall(void);
	void MoveBall(void);
	void MoveRacket(Rectangle* pRacket, Direction pDir); 
	void ComputeGameplay(GameScreen* currentScreen);

	void ComputeGameplayScreen();

};

