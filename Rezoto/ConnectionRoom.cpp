#include "ConnectionRoom.h"
#include "UDPClient.h"
#include <iostream>

ConnectionRoom::ConnectionRoom()
{
    auto textfield = new InputField();
	UiElements.push_back(textfield);
    textfield->SetLabelText("gigigougou");

    Button* JoinButton = new Button(0.0f, 0.0f, 100.0f, 100.0f, std::bind(&ConnectionRoom::Test, this));
    UiElements.push_back(JoinButton);
}

void ConnectionRoom::ComputeLogic(GameClient* gameClient)
{
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
    UDPClient::GetInstance()->Connect("10.1.40.125", 8888);
    std::cout << "button pressed" << std::endl;
}
