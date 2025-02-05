#include "ConnectionRoom.h"
#include <iostream>

ConnectionRoom::ConnectionRoom()
{
    auto UserName = new InputField();
	UiElements.push_back(UserName);
    UserName->SetLabelText("UserName");
    UserName->SetInputFieldType(All);

    auto IP = new InputField();
    UiElements.push_back(IP);
    IP->SetLabelText("IP");
    IP->SetPosition(IP->textBox.x, 300);
    

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
    std::cout << "button pressed" << std::endl;
}
