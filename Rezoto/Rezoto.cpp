#include <iostream>
#include <functional>

#include "GameClient.h"
#include "PongScreen.h"
#include "TitleScreen.h"
#include "ConnectionRoom.h"
//#include "UDPClient.h"

int main(void)
{
    // Network thread
    //UDPClient udpServer;
    //std::thread networkThread(std::bind(&UDPClient::Run, &udpServer));

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
