#include "TitleScreen.h"

#include "GameClient.h"

#include <raylib.h>

void TitleScreen::ComputeLogic(GameClient* gameClient)
{
	if (IsKeyPressed(KEY_ENTER)) 
		gameClient->SetScreen(gameClient->ConnectionRoom);
	gameClient->ResetGame();
}

void TitleScreen::Draw(GameClient* gameClient)
{
	ClearBackground(BLACK);
	DrawText("PONG", 60, 20, 120, GRAY);
	DrawText("Press UP and DOWN arrows for moving paddle", 60, 300, 20, GRAY);
	DrawText("Press ENTER to PLAY", 60, 450, 20, GRAY);
	DrawText("Press ESCAPE to QUIT", 60, 480, 20, GRAY);
}

void TitleScreen::StartScreen(GameClient* gameClient)
{

}
