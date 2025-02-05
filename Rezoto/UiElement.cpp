#include "UiElement.h"

#include <raylib.h>

Rectangle LeRectangle::ToRectangle() const
{
    return { x, y, width, height };
}
