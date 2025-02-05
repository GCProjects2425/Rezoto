#pragma once

#include <string>

class Rectangle;

struct LeRectangle
{
	float x;
	float y;
	float width;
	float height;
	
	LeRectangle() : x(0), y(0), width(0), height(0) {};
	LeRectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {};
	
	struct Rectangle ToRectangle() const;
};

class UiElement
{
public :
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetPosition(int x, int y) = 0;
	virtual void SetLabelText(std::string text) = 0;
};

