#pragma once
#include "GameScreen.h"
#include "vector"
#include "UiElement.h"
#include "InputField.h"
#include "Button.h"

class ConnectionRoom :
	public GameScreen
{
	UIManager* m_UIManager;
	InputField* UsernameField;
	InputField* IpField;
public:
	ConnectionRoom();

	std::vector<UiElement*> UiElements;
	void ComputeLogic(GameClient* gameClient) override;
	void Draw(GameClient* gameClient) override;
	void StartScreen(GameClient* gameClient) override;
	void TryConnectRoom();

	void Test();
};

