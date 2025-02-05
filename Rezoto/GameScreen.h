#pragma once

class GameClient;

class GameScreen
{
public:

	virtual void ComputeLogic(GameClient* gameClient) = 0;
	virtual void Draw(GameClient* gameClient) = 0;
	virtual void StartScreen(GameClient* gameClient) = 0;
};

