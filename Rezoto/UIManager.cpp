#include "UIManager.h"

void UIManager::Update()
{
	m_iFramesCounter++;
	m_iMousePosition = GetMousePosition();
}
