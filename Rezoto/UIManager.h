#pragma once
#include "Singleton.h"
#include "CustomStruct.h"

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
};

