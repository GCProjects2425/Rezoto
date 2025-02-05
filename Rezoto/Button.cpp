#include "Button.h"

#include <raylib.h>

Button::Button(int x, int y, int widht, int height, std::function<void()> function)
{
    m_RectPos = { (float)x, (float)y, (float)widht, (float)height };
    m_Function = function;
    m_UIManager = UIManager::GetInstance();
}

void Button::Update()
{
    // Check button state
    if (CheckCollisionPointRec(m_UIManager->m_iMousePosition.ToVector2(), m_RectPos.ToRectangle()) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        m_Function();
    }
}

void Button::Draw()
{
    DrawRectangleRec(m_RectPos.ToRectangle(), LIGHTGRAY);

    DrawText(m_sLabelText.c_str(), m_RectPos.x + (m_RectPos.width / 2) - MeasureText(m_sLabelText.c_str(), 20) / 2, m_RectPos.y - m_RectPos.height, 20, LIGHTGRAY);
}

void Button::SetPosition(int x, int y)
{
    m_RectPos.x = x;
    m_RectPos.y = y;
}

void Button::SetLabelText(std::string text)
{
    m_sLabelText = text;
}
