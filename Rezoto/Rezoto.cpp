// Ici c'est le jeu
//

#include <iostream>
#include "raylib.h"
#include "pong.h"
#include "PongScreen.h"
#include "TitleScreen.h"

Rectangle textBox = { 800 / 2.0f - 100, 180, 225, 50 };
bool mouseOnText = false;

int main(void)
{
    Pong* pong = new Pong();
    pong->TitleScreen = new TitleScreen;
    pong->PongScreen = new PongScreen;

    pong->SetScreen(pong->TitleScreen);
    pong->InitializeElements();


    //Remove the possibility to close with Escape
    SetExitKey(KEY_NULL);

    // Main loop.
    while (!WindowShouldClose()) // Check ESC key.
    {
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        pong->CurrentScreen->ComputeLogic(pong);

        // Rendering.
        BeginDrawing();
        pong->CurrentScreen->Draw(pong);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
