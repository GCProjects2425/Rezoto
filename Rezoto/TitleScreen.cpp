#include "TitleScreen.h"

void TitleScreen::ComputeLogic(GameClient* gameClient)
{
	if (IsKeyPressed(KEY_ENTER)) 
		gameClient->SetScreen(gameClient->ConnectionRoom);
	gameClient->ResetGame();
}

void TitleScreen::Draw(GameClient* gameClient)
{
	ClearBackground(BLACK);
	DrawText("PONG", 120, 20, 120, GRAY);
	DrawText("Based on Atari PONG", 120, 140, 60, GRAY);
	DrawText("Programmed with Raylib by Angel G. Cuartero", 120, 220, 20, GRAY);
	DrawText("Player 1: Q, A", 120, 390, 20, GRAY);
	DrawText("Player 2: I, J", 120, 420, 20, GRAY);
	DrawText("Press ENTER to PLAY", 120, 450, 20, GRAY);
	DrawText("Press ESCAPE to QUIT", 120, 480, 20, GRAY);
}

void TitleScreen::StartScreen(GameClient* gameClient)
{

}
