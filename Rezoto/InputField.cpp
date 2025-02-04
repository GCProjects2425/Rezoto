#include "InputField.h"
#include <regex>

InputField::InputField(int x, int y, int widht, int height)
{
    m_RectPos = new Rectangle{ (float)x, (float)y, (float)widht, (float)height};
}

void InputField::Update()
{
    //----------------------------------------------------------------------------------
    if (CheckCollisionPointRec(GetMousePosition(), *m_RectPos)) m_bMouseOnText = true;
    else m_bMouseOnText = false;

    if (m_bMouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        std::string IP(m_cContent);

        if (std::regex_match(IP, ipv4))
        {
        }

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((((key >= 48) && (key <= 57)) || key == 46) && (m_iLetterCount < 12))
            {
                m_cContent[m_iLetterCount] = (char)key;
                m_cContent[m_iLetterCount + 1] = '\0'; // Add null terminator at the end of the string.
                m_iLetterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            m_iLetterCount--;
            if (m_iLetterCount < 0) m_iLetterCount = 0;
            m_cContent[m_iLetterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void InputField::Draw()
{
    ClearBackground(BLACK);

    DrawRectangleRec(*m_RectPos, LIGHTGRAY);
    if (m_bMouseOnText) DrawRectangleLines((int)m_RectPos->x, (int)m_RectPos->y, (int)m_RectPos->width, (int)m_RectPos->height, RED);
    else DrawRectangleLines((int)m_RectPos->x, (int)m_RectPos->y, (int)m_RectPos->width, (int)m_RectPos->height, DARKGRAY);

    DrawText(m_cContent, (int)m_RectPos->x + 5, (int)m_RectPos->y + 8, 40, MAROON);
    DrawText(m_sLabelText.c_str(), m_RectPos->x+(m_RectPos->width/2)- MeasureText(m_sLabelText.c_str(), 20) /2, m_RectPos->y-m_RectPos->height, 20, LIGHTGRAY);

    if (m_bMouseOnText)
    {
        if (m_iLetterCount < 12)
        {
            // Draw blinking underscore char
            if (((m_iFramesCounter / 20) % 2) == 0) DrawText("_", (int)m_RectPos->x + 8 + MeasureText(m_cContent, 40), (int)m_RectPos->y + 12, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", m_RectPos->x + (m_RectPos->width / 2) - MeasureText("Press BACKSPACE to delete chars...", 20) / 2, m_RectPos->y + m_RectPos->height, 20, GRAY);
    }
}

void InputField::SetPosition(int x, int y)
{
    m_RectPos->x = x;
    m_RectPos->y = y;
}

void InputField::SetLabelText(std::string text)
{
    m_sLabelText = text;
}
