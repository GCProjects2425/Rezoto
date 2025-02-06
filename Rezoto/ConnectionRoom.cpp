#include "ConnectionRoom.h"
#include "UDPClient.h"
#include <iostream>

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
    if (m_UIManager->IsKeyDown(K_ENTER))
        Test();
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
}

void ConnectionRoom::Test()
{
    UDPClient::GetInstance()->Connect("127.0.0.1", 8888);
    std::cout << "button pressed" << std::endl;
}
