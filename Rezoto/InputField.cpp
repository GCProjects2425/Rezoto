#include "InputField.h"

void InputField::Update()
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
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < 10))
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

    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
    DrawText(labelText.c_str(), textBox.x+(textBox.width/2)- MeasureText(labelText.c_str(), 20) /2, textBox.y-textBox.height, 20, LIGHTGRAY);

    if (mouseOnText)
    {
        if (letterCount < 10)
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
