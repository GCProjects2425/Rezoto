#include "ConnectionRoom.h"

ConnectionRoom::ConnectionRoom()
{
    auto textfield = new InputField();
	UiElements.push_back(textfield);
    textfield->SetLabelText("gigigougou");
}

void ConnectionRoom::ComputeLogic(Pong* pong)
{
    for (auto& element : UiElements) {
        element->Update();
    }
}

void ConnectionRoom::Draw(Pong* pong)
{
    for (auto& element : UiElements) {
        element->Draw();
    }
}

void ConnectionRoom::StartScreen(Pong* pong)
{
}
