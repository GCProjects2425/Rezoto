#include "UIManager.h"
#include <raylib.h>

void UIManager::Update()
{
	m_iFramesCounter++;
	m_iMousePosition = LeVector2(GetMousePosition().x, GetMousePosition().y);
}

bool UIManager::IsKeyDown(CustomKey key)
{
	return RAYLIB_H::IsKeyDown(key);
}

bool UIManager::IsKeyPressed(CustomKey key)
{
	return RAYLIB_H::IsKeyPressed(key);
}
