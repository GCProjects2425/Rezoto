#include "UIManager.h"
#include <raylib.h>

void UIManager::Update()
{
	m_iFramesCounter++;
	m_iMousePosition = LeVector2(GetMousePosition().x, GetMousePosition().y);
}
