#include "ConnectionRoom.h"
#include "UDPClient.h"
#include <iostream>
#include <regex>
#include "Message.h"
#include "GameClient.h"

ConnectionRoom::ConnectionRoom()
{
	m_UIManager = UIManager::GetInstance();

	auto usernameField = new InputField(800 / 2.0f - 100, 180, 225, 50);
	UiElements.push_back(usernameField);
	usernameField->SetLabelText("Username");
	usernameField->SetInputType(InputFieldType::All);

	UsernameField = usernameField;

	auto ipField = new InputField(800 / 2.0f - 100, 330, 225, 50);
	UiElements.push_back(ipField);
	ipField->SetLabelText("IP");
	ipField->SetInputType(InputFieldType::Number);

	IpField = ipField;


	//Button* JoinButton = new Button(0, 0, 225, 50, std::bind(&ConnectionRoom::Test, this));
	////JoinButton->SetLabelText("Join Game");
	//UiElements.push_back(JoinButton);
}

void ConnectionRoom::ComputeLogic(GameClient* gameClient)
{
	if (m_UIManager->IsKeyPressed(K_ENTER))
		TryConnectRoom();
	m_UIManager->Update();
	for (auto& element : UiElements)
	{
		element->Update();
	}
}

void ConnectionRoom::Draw(GameClient* gameClient)
{
	for (auto& element : UiElements)
	{
		element->Draw();
	}
}

void ConnectionRoom::StartScreen(GameClient* gameClient)
{
}

void ConnectionRoom::TryConnectRoom()
{
	std::regex ipRegex(R"(^((25[0-5]|2[0-4][0-9]|1?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|1?[0-9][0-9]?)$)");
	if (!std::regex_match(IpField->m_cContent, ipRegex)) {
		std::cout << "Bad ip";
		return;
	}
	if (strlen(UsernameField->m_cContent) < 2) {
		std::cout << "Username should be at least 2 char";
		return;
	}
	
	UDPClient::GetInstance()->Connect(IpField->m_cContent,8888,UsernameField->m_cContent);
	GameClient::GetInstance()->SetScreen(GameClient::GetInstance()->PongScreen);
}

void ConnectionRoom::Test()
{
	std::cout << "button pressed" << std::endl;
}
