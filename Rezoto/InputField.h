#pragma once
#include "UiElement.h"


enum InputFieldType {
    Number,
    All
};

class InputField :
    public UiElement
{
public:

    RAYLIB_H::Rectangle textBox = { 800 / 2.0f - 100, 180, 225, 50 };
    std::string labelText;
    InputFieldType type = Number;
    bool mouseOnText = false;
    char name[12 + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    int framesCounter = 0;

    void Update() override;
    void Draw() override;
    void SetPosition(int x, int y) override; 
    void SetLabelText(std::string text) override;
    void SetInputFieldType(InputFieldType type);
};

