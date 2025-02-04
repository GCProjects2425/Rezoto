#include "ConnectionRoom.h"

ConnectionRoom::ConnectionRoom()
{
    auto textfield = new InputField();
	UiElements.push_back(textfield);
    textfield->SetLabelText("gigigougou");
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
