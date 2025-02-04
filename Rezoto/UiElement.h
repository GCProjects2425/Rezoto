#pragma once
#include "raylib.h"
#include <string>
class UiElement
{
public :
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetPosition(int x, int y) = 0;
	virtual void SetLabelText(std::string text) = 0;
};

