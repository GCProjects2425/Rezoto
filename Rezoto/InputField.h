#pragma once
#include "UiElement.h"

class InputField : public UiElement
{
    Rectangle* m_RectPos;
    std::string m_sLabelText;
    bool m_bMouseOnText = false;
    int m_iLetterCount = 0;

public:

    InputField(int x, int y, int widht, int height);
    int m_iFramesCounter = 0;
    char m_cContent[12 + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'

    void Update() override;
    void Draw() override;
    void SetPosition(int x, int y) override; 
    void SetLabelText(std::string text) override;
};

