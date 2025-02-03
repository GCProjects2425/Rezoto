// Ici c'est le jeu
//

#include <iostream>
#include "raylib.h"
#include "pong.h"

int main(void)
{
    Pong* pong = new Pong();

  GameScreen currentScreen = TITLE;
    pong->InitializeElements();

    // Main loop.
    while (!WindowShouldClose()) // Check ESC key.
    {
        // Updating.
        switch (currentScreen)
        {
        case TITLE:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                currentScreen = GAMEPLAY;
        } break;
        case GAMEPLAY:
        {
            pong->ComputeGameplay(&currentScreen);
        } break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                currentScreen = GAMEPLAY;
        } break;
        default: break;
        }

        // Rendering.
        BeginDrawing();
        switch (currentScreen)
        {
        case TITLE:
        {
            ClearBackground(BLACK);
            DrawText("PONG", 120, 20, 120, GRAY);
            DrawText("Based on Atari PONG", 120, 140, 60, GRAY);
            DrawText("Programmed with Raylib by Angel G. Cuartero", 120, 220, 20, GRAY);
            DrawText("Player 1: Q, A", 120, 390, 20, GRAY);
            DrawText("Player 2: I, J", 120, 420, 20, GRAY);
            DrawText("Press ENTER to PLAY", 120, 450, 20, GRAY);
            DrawText("Press ESCAPE to QUIT", 120, 480, 20, GRAY);

        } break;
        case GAMEPLAY:
        {
            pong->ComputeGameplayScreen();
        } break;
        case ENDING:
        {
            ClearBackground(BLACK); 
            DrawText(("Winner is Player " + std::to_string(pong->winner)).c_str(), 120, 50, 60, GRAY);

            DrawText("Press ENTER to PLAY AGAIN", 120, 420, 20, GRAY);
            DrawText("Press ESCAPE to QUIT", 120, 450, 20, GRAY);
        } break;
        default: break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
