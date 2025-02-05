#include "CustomStruct.h"
#include <raylib.h>

Rectangle LeRectangle::ToRectangle() const
{
	return { x, y, width, height };
}

Vector2 LeVector2::ToVector2() const
{
	return Vector2();
}
