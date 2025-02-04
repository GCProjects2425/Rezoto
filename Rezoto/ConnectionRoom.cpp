#include "ConnectionRoom.h"
#include <regex>

void ConnectionRoom::ComputeLogic(Pong* pong)
{
    //----------------------------------------------------------------------------------
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();


        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow numbers and dot
            if ((((key >= 48) && (key <= 57)) || key == 46) && (letterCount < 12))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        std::string IP(name);

        if (std::regex_match(IP, ipv4))
        {
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);


}

void ConnectionRoom::Draw(Pong* pong)
{
    ClearBackground(BLACK);

    DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 10), 315, 250, 20, DARKGRAY);

    if (mouseOnText)
    {
        if (letterCount < 10)
        {
            // Draw blinking underscore char
            if ((( framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }
}

void ConnectionRoom::StartScreen(Pong* pong)
{
}
