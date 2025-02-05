#pragma once
#include "UiElement.h"
#include "UIManager.h"

enum InputFieldType {
    Number,
    All
};

class InputField : public UiElement
{
    LeRectangle* m_RectPos;
    std::string m_sLabelText;
    int m_iLetterCount = 0;
    InputFieldType type = Number;
    UIManager* m_UIManager;
    bool m_bMouseOnText = false;

public:

    InputField(int x, int y, int widht, int height);
    char m_cContent[12 + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'

    void Update() override;
    void Draw() override;
    void SetPosition(int x, int y) override; 
    void SetLabelText(std::string text) override;
    void SetInputType(InputFieldType newType);
};


