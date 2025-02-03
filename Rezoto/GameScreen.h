#pragma once
#include "raylib.h"
class Pong; 

class GameScreen
{
public:

	virtual void ComputeLogic(Pong* pong) = 0;
	virtual void Draw(Pong* pong) = 0;
	virtual void StartScreen(Pong* pong) = 0;
};

