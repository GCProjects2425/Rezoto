#include <iostream>
#include "raylib.h"
#include "GameClient.h"
#include "PongScreen.h"
#include "TitleScreen.h"
#include "ConnectionRoom.h"

Rectangle textBox = { 800 / 2.0f - 100, 180, 225, 50 };
bool mouseOnText = false;

int main(void)
{
    GameClient* gameClient = new GameClient();
    gameClient->TitleScreen = new TitleScreen;
    gameClient->PongScreen = new PongScreen;
    gameClient->ConnectionRoom = new ConnectionRoom;
    gameClient->SetScreen(gameClient->TitleScreen);
    gameClient->InitializeElements();


    //Remove the possibility to close with Escape
    SetExitKey(KEY_NULL);

    // Main loop.
    while (!WindowShouldClose()) // Check ESC key.
    {
        /*if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);*/

        gameClient->CurrentScreen->ComputeLogic(gameClient);

        // Rendering.
        BeginDrawing();
        gameClient->CurrentScreen->Draw(gameClient);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
