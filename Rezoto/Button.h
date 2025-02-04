#pragma once
#include "UiElement.h"
#include <functional>

class Button :
    public UiElement
{
    std::function<void()> m_Function;
    std::string m_sLabelText;
public :
    Button(float x, float y, float widht, float height, std::function<void()> function);

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    Rectangle* m_RectPos;

    void Update() override;
    void Draw() override;
    void SetPosition(int x, int y) override;
    void SetLabelText(std::string text) override;
};
