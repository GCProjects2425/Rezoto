#include "ConnectionRoom.h"
#include "UDPClient.h"
#include <iostream>

ConnectionRoom::ConnectionRoom()
{
    m_UIManager = UIManager::GetInstance();

    auto textfield = new InputField(800 / 2.0f - 100, 180, 225, 50);
	UiElements.push_back(textfield);
    textfield->SetLabelText("gigigougou");

    Button* JoinButton = new Button(0, 0, 100, 100, std::bind(&ConnectionRoom::Test, this));
    UiElements.push_back(JoinButton);
}

void ConnectionRoom::ComputeLogic(GameClient* gameClient)
{
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

void ConnectionRoom::Test()
{
    UDPClient::GetInstance()->Connect("127.0.0.1", 8888);
    std::cout << "button pressed" << std::endl;
}
