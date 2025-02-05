#include "InputField.h"
#include <regex>

#include <raylib.h>


void InputField::Update()
{
    //----------------------------------------------------------------------------------
    if (CheckCollisionPointRec(GetMousePosition(), textBox.ToRectangle())) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        std::string IP(name);

        if (std::regex_match(IP, ipv4))
        {
        }

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((((key >= 48) && (key <= 57)) || key == 46) && (letterCount < 12))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
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

void InputField::Draw()
{
    ClearBackground(BLACK);

    DrawRectangleRec(textBox.ToRectangle(), LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
    DrawText(labelText.c_str(), textBox.x+(textBox.width/2)- MeasureText(labelText.c_str(), 20) /2, textBox.y-textBox.height, 20, LIGHTGRAY);

    if (mouseOnText)
    {
        if (letterCount < 12)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", textBox.x + (textBox.width / 2) - MeasureText("Press BACKSPACE to delete chars...", 20) / 2, textBox.y + textBox.height, 20, GRAY);
    }
}

void InputField::SetPosition(int x, int y)
{
    textBox.x = x;
    textBox.y = y;
}

void InputField::SetLabelText(std::string text)
{
    labelText = text;
}
