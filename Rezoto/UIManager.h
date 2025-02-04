#pragma once
#include "Singleton.h"

class UIManager final : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;
public:
	//Unused yet
	int m_iScreenWidth = 800;
	int m_iScreenHeight = 600;


};

