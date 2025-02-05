#pragma once
#include "Singleton.h"
#include <raylib.h>

class UIManager final : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;
public:
	//Unused yet
	int m_iScreenWidth = 800;
	int m_iScreenHeight = 600;

	int m_iFramesCounter = 0;
	Vector2 m_iMousePosition;

	void Update();
};

