#include "Button.h"

#include <raylib.h>

Button::Button(float x, float y, float widht, float height, std::function<void()> function)
{
	m_RectPos = new Rectangle { x, y, widht, height };
    m_Function = function;
}

void Button::Update()
{
    // Check button state
    if (CheckCollisionPointRec(GetMousePosition(), *m_RectPos))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) m_Function();
    }
}

void Button::Draw()
{
    DrawRectangleRec(*m_RectPos, LIGHTGRAY);

    DrawText(m_sLabelText.c_str(), m_RectPos->x + (m_RectPos->width / 2) - MeasureText(m_sLabelText.c_str(), 20) / 2, m_RectPos->y - m_RectPos->height, 20, LIGHTGRAY);
}

void Button::SetPosition(int x, int y)
{
    m_RectPos->x = x;
    m_RectPos->y = y;
}

void Button::SetLabelText(std::string text)
{
    m_sLabelText = text;
}
