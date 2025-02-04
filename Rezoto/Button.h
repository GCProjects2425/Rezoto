#pragma once
#include "UiElement.h"
class Button :
    public UiElement
{
public :
    void Update() override;
    void Draw() override;
};

