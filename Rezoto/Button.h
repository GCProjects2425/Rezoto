#pragma once
#include "UiElement.h"
#include <functional>

class Button : public UiElement
{
    std::function<void()> m_Function;
    Rectangle* m_RectPos;
    std::string m_sLabelText;
    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED

public :
    Button(int x, int y, int widht, int height, std::function<void()> function);

    void Update() override;
    void Draw() override;
    void SetPosition(int x, int y) override;
    void SetLabelText(std::string text) override;
};
