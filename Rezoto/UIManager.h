#pragma once
#include "Singleton.h"
#include "CustomStruct.h"
enum CustomKey {
	K_UP = 265,
	K_DOWN = 264,
	K_ENTER = 257,
	K_ESCAPE = 256
};

class UIManager final : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;
public:
	//Unused yet
	int m_iScreenWidth = 800;
	int m_iScreenHeight = 600;

	int m_iFramesCounter = 0;
	LeVector2 m_iMousePosition;

	void Update();
	bool IsKeyDown(CustomKey key);
	bool IsKeyPressed(CustomKey key);
};

